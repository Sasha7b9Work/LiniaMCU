// 2025/10/15 16:05:06 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Hardware/HAL/HAL_PINS.h"


struct Chip
{
    Chip(uint _l, PinOut *_cs, PinOut *_clk) : cs(_cs), clk(_clk), length(_l) { }

    void SetLength(uint _length)
    {
        length = _length;
    }

private:

    PinOut *cs;
    PinOut *clk;

    uint length = 0;
};


struct ChipDAC : public Chip
{
    ChipDAC(uint _l, PinOut *_cs, PinOut *_clk, PinOut *_out) : Chip(_l, _cs, _clk), out(_out) { }

    void Write(uint /*value*/)
    {
    }

private:

    PinOut *out;
};


struct ChipREG : public Chip
{
    ChipREG(uint _l, PinOut *_cs, PinOut *_clk, PinOut *_out) : Chip(_l, _cs, _clk), out(_out) { }

    void Write(uint /*value*/)
    {
    }

private:

    PinOut *out;
};


extern ChipDAC dacs[10];
extern ChipREG regs[10];
