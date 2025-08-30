// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "common/Command.h"
#include "common/Messages.h"
#include "Utils/Queue.h"


namespace DInterface
{
    void Update();

    // ���������� ������ �� ������� ���������, ��������� ��������
    Queue &GetOutbox();

    void ResetFreqForSend();

    // ��������� ��������� � ������� ��������. ���� ������� ���������, ��������� ��������� � ������� ���������� false
    bool AddMessageForTransmit(SimpleMessage *message);
};
