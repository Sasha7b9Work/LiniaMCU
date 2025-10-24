// 2025/10/24 09:30:11 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Hardware/HAL/HAL_PINS.h"


// ���������� ��� ������ �������

// ����� ����
namespace ChanB
{
    extern PinOut pin3_50_V;        // ���������� ����� �������� ����������/����� �������� ����
    extern PinOut pinEND1B;         // ���������� DAC
    extern PinOut pinEND2B;         // ���������� DAC
    extern PinOut pinENRGB;         // ���������� ��������
}


// XP5 - ����� ��������
namespace ChanS
{
    extern PinOut pinEND1P;         // ���������� DAC
    extern PinOut pinEND2P;         // ���������� DAC
    extern PinOut pinENRGP;         // ���������� ��������
}


// XP6, XP7 - ���������� ����, ������������� �������� (����� ����������)
namespace ChanC
{
    extern PinOut pinRAZV_ENDU;       // ���������� ���������� U ����� ��������
    extern PinOut pinRAZV_ENRGF;      // ���������� ��������

    extern PinOut pinMEAS_I_ENRGI;    // ����� �������� ��������� ����
    extern PinOut pinMEAS_I_SPEED;
}
