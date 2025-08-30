// 2025/08/30 18:38:38 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


struct PinMode
{
    enum E
    {
        Out,
        In,
        Count
    };
};

class Pin
{
public:

    Pin(void *port, uint16 pin, PinMode::E);

private:

    void      *port;
    uint16     pint;
    PinMode::E mode;
};


class PinIn : public Pin
{

};


class PinOut : public Pin
{

};


// ����� ����
extern PinOut pB_3_50_V;        // PG11 57  ���������� ����� �������� ����������/����� �������� ����
extern PinOut pB_END1B;         // PC3  29  ���������� DAC
extern PinOut pB_END2B;         // PC2  28  ���������� DAC
extern PinOut pB_ENRGB;         // PC1  27  ���������� ��������

// ����� ��������
extern PinOut pS_END1P;         // PC0  26  ���������� DAC
extern PinOut pS_END2P;         // PF10 22  ���������� DAC
extern PinOut pS_ENDRGP;        // PF9  21  ���������� ��������

// ���������� ����
extern PinOut pMEAS_I_SPEED;    // PG11 126
extern PinOut pMEAS_I_ENRGI;    //      11  ���������� ��������

// ������������� ��������
extern PinOut pRAZV_ENDU;       // PC15 9   ���������� ���������� U ����� ��������
extern PinOut pRAZV_ENRGF;      // PF0  10  ���������� ��������

// �������� 50V
extern PinOut pSOURCE_50V_50EP; // PA6  42
extern PinOut pSOURCE_50V_50EN; // PF11 49

// ����������
extern PinIn  pCOMM_3000VE;     // PC4  44
extern PinIn  pCOMM_200EN;      // PC5  45
extern PinIn  pCOMM_200EP;      // PB0  46
extern PinIn  pCOMM_20EN;       // PB1  47
extern PinIn  pCOMM_20EP;       // PB2  48
extern PinOut pCOMM_ENRGK;      // PF7  19  ���������� ��������

// �������� 3 ��
extern PinOut pin_SOURCE_3kV_ENRGV; // PF8  20  ���������� �������� ��������� ���������� 3��

// ����
extern PinIn  pFPGA_LIMIT;      // PE7  58
extern PinOut pFPGA_A0_RG;      // PG5  90
extern PinOut pFPGA_A1_RG;      // PG6  91
extern PinOut pFPGA_A2_RG;      // PG3  89
extern PinOut pFPGA_CLK_RG;     // PG7  92
extern PinOut pFPGA_WR_RG;      // PG8  93
extern Pin    pFPGA_DAT_RG;     // PD13 82
extern Pin    pFPGA_ST_TB;      //      15

// Orange Pi
extern PinOut pPI_ENB_STM;      // PD12 81
extern Pin    pPI_TX;           // PB6  136
extern Pin    pPI_RX;           // PA10 102

// ����� ����, ����� ��������
extern PinOut pDAT1_DAC;        // PD8  77
extern PinOut pCLK1_DAC;        // PD11 80

// ���������� ����, ������������� ��������, ����������, �������� ���������� 3��
extern PinOut pDAT2_DAC;        // PB15 76
extern PinOut pCLK2_DAC;        // PD9  78
