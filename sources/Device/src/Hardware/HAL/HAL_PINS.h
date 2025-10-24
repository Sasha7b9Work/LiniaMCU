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

//------------------ Канал базы, канал подложки
extern PinOut pDAT1_DAC;        // PD8  77
extern PinOut pCLK1_DAC;        // PD11 80

//------------------ Измеритель тока, формирователь развёртки, коммутатор, источник напряжения 3кВ
extern PinOut pDAT2_DAC;        // PB15 76
extern PinOut pCLK2_DAC;        // PD9  78
