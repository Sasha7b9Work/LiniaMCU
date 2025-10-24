// 2025/08/30 18:38:38 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


struct Port
{
    enum E
    {
        _A,
        _B,
        _C,
        _D,
        _E,
        _F,
        _G,
        _H,
        _I,
        Count
    };
};


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

    enum E
    {
        _0,
        _1,
        _2,
        _3,
        _4,
        _5,
        _6,
        _7,
        _8,
        _9,
        _10,
        _11,
        _12,
        _13,
        _14,
        _15,
        Count
    };

    Pin(Port::E, Pin::E, PinMode::E);

    void Init();

protected:

    void      *port;
    uint16     pin;
    PinMode::E mode;
};


class PinIn : public Pin
{
public:
    PinIn(Port::E _port, Pin::E _pin) : Pin(_port, _pin, PinMode::In) { }
};


class PinOut : public Pin
{
public:
    PinOut(Port::E _port, Pin::E _pin) : Pin(_port, _pin, PinMode::Out) { }
    void ToLow();
    void ToHi();
    void Set(bool);
};


namespace HAL_PINS
{
    void Init();
}


// Orange Pi
extern PinOut pPI_ENB_STM;      // PD12 81
extern Pin    pPI_TX;           // PB6  136
extern Pin    pPI_RX;           // PA10 102

// ����
extern PinIn  pFPGA_LIMIT;      // PE7  58
extern PinOut pFPGA_A0_RG;      // PG5  90
extern PinOut pFPGA_A1_RG;      // PG6  91
extern PinOut pFPGA_A2_RG;      // PG3  89
extern PinOut pFPGA_CLK_RG;     // PG7  92
extern PinOut pFPGA_WR_RG;      // PG8  93
extern PinOut pFPGA_DAT_RG;     // PD13 82
extern Pin    pFPGA_ST_TB;      //      15

//------------------ ����� ����, ����� ��������
extern PinOut pDAT1_DAC;        // PD8  77
extern PinOut pCLK1_DAC;        // PD11 80
// XP4 ����� ����
extern PinOut pB_3_50_V;        // PG11 57  ���������� ����� �������� ����������/����� �������� ����
extern PinOut pB_END1B;         // PC3  29  ���������� DAC
extern PinOut pB_END2B;         // PC2  28  ���������� DAC
extern PinOut pB_ENRGB;         // PC1  27  ���������� ��������
// XP5 ����� ��������
extern PinOut pS_END1P;         // PC0  26  ���������� DAC
extern PinOut pS_END2P;         // PF10 22  ���������� DAC
extern PinOut pS_ENRGP;         // PF9  21  ���������� ��������

//------------------ ���������� ����, ������������� ��������, ����������, �������� ���������� 3��
extern PinOut pDAT2_DAC;        // PB15 76
extern PinOut pCLK2_DAC;        // PD9  78
// XP13 �������� 3 ��
extern PinOut pSOURCE_3kV_ENRGV; // PF8  20  ���������� �������� ��������� ���������� 3��

// XP6 ���������� ����
extern PinOut pMEAS_I_SPEED;    // PG11 126


//------------------- ����� C----------------------------------
extern PinOut pMEAS_I_ENRGI;    //      11  ����� �������� ��������� ����
extern PinOut pRAZV_ENDU;       // PC15 9   ���������� ���������� U ����� ��������
extern PinOut pRAZV_ENRGF;      // PF0  10  ���������� ��������
