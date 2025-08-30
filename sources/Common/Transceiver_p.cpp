// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "common/Transceiver.h"
#include "Display/Colors.h"
#include "Hardware/CPU.h"
#include "Hardware/Timer.h"
#include "Hardware/HAL/HAL.h"
#include "Utils/Debug.h"


void Transceiver::Transmit(SimpleMessage *message)
{
    int timeout = (message->Size() > 1000) ? 100 : 10;

    bool result = false;

    while (!result)
    {
        HAL_SPI4::WaitRelease();                                                // ������� �������� ����� ���������� ������� � ��������� "��������"

        for (int i = 0; i < 2; i++)
        {
            HAL_SPI4::Transmit(message->Size(), 10);                                // ������� ������ ������������ ������

            HAL_SPI4::Transmit(message->TakeData(), message->Size(), timeout);      // ������� ��������������� ������

            uint newSize = 0;
            HAL_SPI4::Receive(&newSize, 4, 10);                                     // ������ ��������� ������ ������, ������� ����� �������� ��� ����������

            uint trashedBytes = HAL_SPI4::ReceiveAndCompare(message->TakeData(), message->Size());

            result = (trashedBytes == 0);
        }
    };
}


bool Transceiver::Receive(SimpleMessage *message)
{
    HAL_SPI4::WaitRelease();

    int size = 0;
    HAL_SPI4::Receive(&size, 4, 10);

    if (message->AllocateMemory(size))
    {
        HAL_SPI4::Receive(message->TakeData(), message->Size(), 50);

        return true;
    }

    return message->Size() != 0;
}
