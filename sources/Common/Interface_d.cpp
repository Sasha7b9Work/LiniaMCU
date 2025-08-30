// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "common/Messages.h"
#include "common/Transceiver.h"
#include "common/Handlers_d.h"
#include "common/Interface_d.h"
#ifdef LOADER
#include "FDrive/FDrive_dl.h"
#else
#include "FDrive/FDrive_d.h"
#endif
#include "Generator/Generator_d.h"
#include "Hardware/CPU.h"
#include "Hardware/Timer.h"
#include "Hardware/HAL/HAL.h"
#include "Settings/CalibrationSettings.h"
#include "Utils/Queue.h"
#include "Utils/StringUtils.h"
#include "common/Command.h"
#include "structs.h"
#include <cstdlib>


namespace DInterface
{
    // ������� ���������, ��������� ��������
    static Queue outbox;

    // ��������� �������� ��������, ��� ��� ������� �������� � ������ ��� ���������� ������������ ��������
    uint freqForSend = MAX_UINT;
}


Queue &DInterface::GetOutbox()
{
    return outbox;
}


void DInterface::ResetFreqForSend()
{
    freqForSend = MAX_UINT;
}


void DInterface::Update()
{
    CPU::SetReady();

    int size = 0;

    if (HAL_SPI1::Receive(&size, 4, 10))                                                           // ����� ������ ������������ ���������
    {
        SimpleMessage first;              // ���� ��������� ������ ���������
        SimpleMessage second;             // ���� ��������� ������ ���������

        int timeout = size > 100 ? 200 : 10;

        if (first.AllocateMemory(size))
        {
            if (HAL_SPI1::Receive(first.TakeData(), first.Size(), timeout))                            // ��������� ������
            {
                if (HAL_SPI1::Transmit(&size, 4, timeout))                                         // ������� ��� ������
                {
                    if (HAL_SPI1::Transmit(first.TakeData(), first.Size(), timeout))                   // � ������
                    {
                        if (HAL_SPI1::Receive(&size, 4, 10))
                        {
                            if (second.AllocateMemory(size))                                    // ������ ��� ��������� ����� ��������� � ���� �����
                            {
                                if (HAL_SPI1::Receive(second.TakeData(), second.Size(), timeout))      // ��� � ������
                                {
                                    size = second.Size();

                                    if (HAL_SPI1::Transmit(&size, 4, timeout))
                                    {
                                        if (HAL_SPI1::Transmit(second.TakeData(), second.Size(), timeout))
                                        {
                                            if (second.IsEquals(&first))                        // ���������, ������� �� ��� �������� ���������
                                            {
                                                DHandlers::Processing(&first);
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    CPU::SetBusy();
}


bool DInterface::AddMessageForTransmit(SimpleMessage *message)
{
    SimpleMessage *clone = message->Clone();

    if (!outbox.Push(clone))
    {
        delete clone;
        // \tood ����� ����� �������� �� ������. ������� ���, ����� ��������� �� ������� �������� ����������������� �������� - �������� �� � ������� ���� ����� ��� ��� ����� (����������)
        // LOG_ERROR("������� �����������");
        return false;
    }

    return true;
}


void SimpleMessage::Transmit()
{
    DInterface::AddMessageForTransmit(this);
}


void SimpleMessage::TransmitAndSend()
{
    Transmit();

    while(DInterface::GetOutbox().Size())
    {
        DInterface::Update();
    }
}
