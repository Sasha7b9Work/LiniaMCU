// 2025/10/15 16:04:55 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Device/Chips.h"


ChipDAC dacs[10] =
{
    { nullptr, nullptr, nullptr },
    { nullptr, nullptr, nullptr },
    { nullptr, nullptr, nullptr },
    { nullptr, nullptr, nullptr },
    { nullptr, nullptr, nullptr },
    { nullptr, nullptr, nullptr },
    { nullptr, nullptr, nullptr },
    { nullptr, nullptr, nullptr },
    { nullptr, nullptr, nullptr },
    { nullptr, nullptr, nullptr }
};


ChipREG regs[10] =
{
    { nullptr, nullptr, nullptr },
    { nullptr, nullptr, nullptr },
    { nullptr, nullptr, nullptr },
    { nullptr, nullptr, nullptr },
    { nullptr, nullptr, nullptr },
    { nullptr, nullptr, nullptr },
    { nullptr, nullptr, nullptr },
    { nullptr, nullptr, nullptr },
    { nullptr, nullptr, nullptr },
    { nullptr, nullptr, nullptr }
};


namespace Chips
{
    namespace ADC
    {
        static uint lengths[10];
    }
}


void Chips::ADC::SetLength(int num_chip, uint length)
{
    lengths[num_chip] = length;
}


uint Chips::ADC::Read(int /*num*/)
{
    return 0;
}
