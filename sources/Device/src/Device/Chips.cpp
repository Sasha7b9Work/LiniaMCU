// 2025/10/15 16:04:55 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Device/Chips.h"


ChipDAC dacs[10] =
{   //      cs       clk      out
    { 12, nullptr, nullptr, nullptr },  // XP7 ������������� �������� � ���������� ����������. ����������� � PCM
    { 12, nullptr, nullptr, nullptr },  // XP7 ������������� �������� � ���������� ����������
    { 12, nullptr, nullptr, nullptr },  // ��������-���������� (����� ����)
    { 12, nullptr, nullptr, nullptr },  // ��������-���������� (����� ����)
    { 12, nullptr, nullptr, nullptr },  // ��������-���������� (�������������� �����)
    { 12, nullptr, nullptr, nullptr },  // ��������-���������� (�������������� �����)
    { 12, nullptr, nullptr, nullptr },  // �������� ���������� 50 �
    { 0,  nullptr, nullptr, nullptr },
    { 0,  nullptr, nullptr, nullptr },
    { 0,  nullptr, nullptr, nullptr }
};


ChipREG regs[10] =
{
    { 24, &pin_SOURCE_3kV_ENRGV, &pCLK2_DAC, &pDAT2_DAC },  // �������� ���������� 3000�
    { 16, &pCOMM_ENRGK,          &pCLK2_DAC, &pDAT2_DAC },  // ����������
    { 32, &pRAZV_ENRGF,          &pCLK2_DAC, &pDAT2_DAC },  // ������������� �������� � ���������� ����������
    { 32, &pB_END2B,             &pCLK1_DAC, &pDAT1_DAC },  // ��������-���������� (����� ����)
    { 32, &pS_ENDRGP,            &pCLK1_DAC, &pDAT1_DAC },  // ��������-���������� (�������������� �����)
    { 16, &pMEAS_I_ENRGI,        &pCLK2_DAC, &pDAT2_DAC },  // ���������� ����
    { 8,  &pSOURCE_50V_50EN,     nullptr,    nullptr },  // �������� ���������� 50 �
    { 0,  nullptr,               nullptr,    nullptr },
    { 0,  nullptr,               nullptr,    nullptr },
    { 0,  nullptr,               nullptr,    nullptr }
};
