// 2025/09/22 13:39:03 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Device/FPGA.h"
#include "Hardware/HAL/HAL_PINS.h"


namespace FPGA
{
    static uint lengths[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
}


void FPGA::Init()
{
    pinCLK_RG.ToLow();
    pinWR_RG.ToLow();
}


void FPGA::Reg::SetLength(int num, uint length)
{
    lengths[num] = length;
}


void FPGA::Reg::Write(int num, uint value)
{
    pinA0_RG.Set(_GET_BIT(num, 0) != 0);
    pinA1_RG.Set(_GET_BIT(num, 1) != 0);
    pinA2_RG.Set(_GET_BIT(num, 2) != 0);

    int length = (int)lengths[num];

    for (int bit = length - 1; bit >= 0; bit--)
    {
        pinDAT_RG.Set(_GET_BIT(value, bit) != 0);
        pinCLK_RG.ToHi();
        pinCLK_RG.ToLow();
    }

    pinWR_RG.ToHi();
    pinWR_RG.ToLow();
}
