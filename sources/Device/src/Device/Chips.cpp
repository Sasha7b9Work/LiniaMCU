// 2025/10/15 16:04:55 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Device/Chips.h"


ChipDAC dacs[10] =
{
    { nullptr, nullptr, nullptr },  // ������������� �������� � ���������� ����������
    { nullptr, nullptr, nullptr },  // ������������� �������� � ���������� ����������
    { nullptr, nullptr, nullptr },  // ��������-���������� (����� ����)
    { nullptr, nullptr, nullptr },  // ��������-���������� (����� ����)
    { nullptr, nullptr, nullptr },  // ��������-���������� (�������������� �����)
    { nullptr, nullptr, nullptr },  // ��������-���������� (�������������� �����)
    { nullptr, nullptr, nullptr },  // �������� ���������� 50 �
    { nullptr, nullptr, nullptr },
    { nullptr, nullptr, nullptr },
    { nullptr, nullptr, nullptr }
};


ChipADC adcs[10] =
{
    { nullptr, nullptr, nullptr },  // ������������� �������� � ���������� ����������
    { nullptr, nullptr, nullptr },  // ��������-���������� (����� ����)
    { nullptr, nullptr, nullptr },  // ��������-���������� (�������������� �����)
    { nullptr, nullptr, nullptr },  // ���������� ����
    { nullptr, nullptr, nullptr },
    { nullptr, nullptr, nullptr },
    { nullptr, nullptr, nullptr },
    { nullptr, nullptr, nullptr },
    { nullptr, nullptr, nullptr },
    { nullptr, nullptr, nullptr }
};


ChipREG regs[10] =
{
    { &pin_SOURCE_3kV_ENRGV, nullptr, nullptr },  // �������� ���������� 3000�
    { &pCOMM_ENRGK,          nullptr, nullptr },  // ����������
    { &pRAZV_ENRGF,          nullptr, nullptr },  // ������������� �������� � ���������� ����������
    { &pB_END2B,             nullptr, nullptr },  // ��������-���������� (����� ����)
    { &pS_ENDRGP,            nullptr, nullptr },  // ��������-���������� (�������������� �����)
    { &pMEAS_I_ENRGI,        nullptr, nullptr },  // ���������� ����
    { &pSOURCE_50V_50EN,     nullptr, nullptr },  // �������� ���������� 50 �
    { nullptr,               nullptr, nullptr },
    { nullptr,               nullptr, nullptr },
    { nullptr,               nullptr, nullptr }
};
