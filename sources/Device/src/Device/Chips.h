// 2025/10/15 16:05:06 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Hardware/HAL/HAL_PINS.h"


/*
*   Здесь всё, что относится к управлению регистрами и ЦАП-ми всех блоков
*/


struct Chip
{
    Chip(uint _l, PinOut *_cs, PinOut *_clk) : cs(_cs), clk(_clk), length(_l) { }

    void SetLength(uint _length)
    {
        length = _length;
    }

protected:

    PinOut *cs;
    PinOut *clk;

    uint length = 0;
};


struct ChipDAC : public Chip
{
    enum E
    {
        CHAN_C_PCM,
        CHAN_C_RANGE,
        CHAN_B_1,
        CHAN_B_2,
        CHAN_S_1,
        CHAN_S_2,
        SOURCE_50V
    };

    ChipDAC(uint _l, PinOut *_cs, PinOut *_clk, PinOut *_dat) : Chip(_l, _cs, _clk), dat(_dat) { }

    void Write(uint);

private:

    PinOut *dat;
};


struct ChipREG : public ChipDAC
{
    enum E
    {
        SOURCE_3kV,
        COMMUTATOR,
        CHAN_C,
        CHAN_B,
        CHAN_S,
        MEAS_I
    };

    ChipREG(uint _l, PinOut *_cs, PinOut *_clk, PinOut *_dat) : ChipDAC(_l, _cs, _clk, _dat) { }
};


extern ChipDAC dacs[10];
extern ChipREG regs[10];
