// 2022/08/30 12:22:42 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Generator/FPGA/RegistersFPGA.h"
#include "Hardware/HAL/HAL_PIO.h"
#include "Utils/Math.h"
#include "Hardware/HAL/HAL.h"
#include "Generator/FPGA/Clock.h"
#include "Hardware/HAL/HAL.h"
#include "structs.h"


namespace FPGA
{
    namespace Register
    {
        // ��������� ���������� ��������
        static uint64 content[Clock::Impulse::Count][Count] =
        {
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
        };

        // ���������� �� A0_RG...A3_RG �����, ������������� ��������
        static void WriteAddress(E);

        void RewriteRegister(E);
    }
}


void FPGA::Register::Write(const E reg, const uint64 _value, const uint64 _value1MHz)
{
    static const int numBits[Register::Count] =
    {
        16, // _0_Control,
        40, // _1_Freq,
        20, // _2_Amplitude,
        28, // _3_RectA,
        28, // _4_RectB,
        32, // _5_PeriodImpulseA,
        32, // _6_DurationImpulseA,
        32, // _7_PeriodImpulseB,
        32, // _8_DurationImpulseB,
        13, // _9_FreqMeter
        28, // _10_Offset
        2   // _11_Start
    };

    content[Clock::Impulse::_100MHz][reg] = _value;
    content[Clock::Impulse::_1MHz][reg] = _value1MHz;

    BitSet64 value;

    value.dword = _value;

    if (reg >= _5_PerImp_Freq_A_PerPack && reg <= _8_DurImp_B)
    {
        HAL_TIM::Delay(1);

        if (Clock::Impulse::Is1MHz())
        {
            value.dword = _value1MHz;
        }
    }

    WriteAddress(reg);

    for (int i = 0; i < 2; i++)
    {
        for (int bit = numBits[reg] - 1; bit >= 0; bit--)
        {
            HAL_PIO::Write(WR_FPGA_DT_RG, Bit::Get(value.dword, bit));    // ������������� ��� ���������� ��������������� ���
            HAL_PIO::Set(WR_FPGA_CLK_RG);                           // � ���������� ��� � ����
            HAL_PIO::Reset(WR_FPGA_CLK_RG);
        }
    }

    HAL_PIO::Set(WR_FPGA_WR_RG);                                    // ������ ������������ ������ �� ����������� �������� � FPGA
    HAL_PIO::Reset(WR_FPGA_WR_RG);
    HAL_TIM::Delay(10);                                             // ��� 10 �����������, ���� ������ ����������� � FPGA

    if (reg >= _5_PerImp_Freq_A_PerPack && reg <= _8_DurImp_B)
    {
        HAL_TIM::Delay(1);
    }
}


void FPGA::Register::RewriteImpulseRegisters()
{
    RewriteRegister(_5_PerImp_Freq_A_PerPack);
    RewriteRegister(_6_DurImp_A_NumbImp);
    RewriteRegister(_7_PerImp_Freq_B_DelayStartStop);
    RewriteRegister(_8_DurImp_B);
}


void FPGA::Register::RewriteRegister(E reg)
{
    Write(reg, content[Clock::Impulse::_100MHz][reg], content[Clock::Impulse::_1MHz][reg]);
}


void FPGA::Register::WriteAddress(E reg)
{
    HAL_PIO::Write(WR_FPGA_A0_RG, Bit::Get(reg, 0));
    HAL_PIO::Write(WR_FPGA_A1_RG, Bit::Get(reg, 1));
    HAL_PIO::Write(WR_FPGA_A2_RG, Bit::Get(reg, 2));
    HAL_PIO::Write(WR_FPGA_A3_RG, Bit::Get(reg, 3));
}


uint64 FPGA::Register::Read(const E reg)
{
    return content[0][reg];
}
