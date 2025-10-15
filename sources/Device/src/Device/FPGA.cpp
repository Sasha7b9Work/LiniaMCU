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
    pFPGA_CLK_RG.ToLow();
    pFPGA_WR_RG.ToLow();
}


void FPGA::Reg::SetLength(int num, uint length)
{
    lengths[num] = length;
}


void FPGA::Reg::Write(int num, uint value)
{
    pFPGA_A0_RG.Set(_GET_BIT(num, 0) != 0);
    pFPGA_A1_RG.Set(_GET_BIT(num, 1) != 0);
    pFPGA_A2_RG.Set(_GET_BIT(num, 2) != 0);

    int length = (int)lengths[num];

    for (int bit = length - 1; bit >= 0; bit--)
    {
        pFPGA_DAT_RG.Set(_GET_BIT(value, bit) != 0);
        pFPGA_CLK_RG.ToHi();
        pFPGA_CLK_RG.ToLow();
    }

    pFPGA_WR_RG.ToHi();
    pFPGA_WR_RG.ToLow();
}
