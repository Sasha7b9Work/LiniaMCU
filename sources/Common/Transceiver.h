// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Messages.h"


/*

    �������� ������ ������������� ���.

*/


namespace Transceiver
{
    void Transmit(SimpleMessage *message);

    bool Receive(SimpleMessage *message);
};
