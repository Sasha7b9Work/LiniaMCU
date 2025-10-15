// 2025/10/15 16:05:06 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Hardware/HAL/HAL_PINS.h"


struct Chip
{
    Chip(PinOut *_cs, PinOut *_clk) : cs(_cs), clk(_clk) { }

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
    ChipDAC(PinOut *_cs, PinOut *_clk, PinOut *_out) : Chip(_cs, _clk), out(_out) { }

    void Write(uint /*value*/)
    {
    }

private:

    PinOut *out;
};


struct ChipREG : public Chip
{
    ChipREG(PinOut *_cs, PinOut *_clk, PinOut *_out) : Chip(_cs, _clk), out(_out) { }

    void Write(uint /*value*/)
    {
    }

private:

    PinOut *out;
};


struct ChipADC : public Chip
{
    ChipADC(PinOut *_cs, PinOut *_clk, PinIn *_in) : Chip(_cs, _clk), in(_in)
    {
    }

    void Write(uint /*value*/)
    {
    }

    uint Read()
    {
        return 0;
    }

private:

    PinIn *in;
};


extern ChipDAC dacs[10];
extern ChipREG regs[10];
extern ChipADC adcs[10];
