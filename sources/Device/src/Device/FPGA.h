// 2025/09/22 13:39:17 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Hardware/HAL/HAL_PINS.h"


namespace FPGA
{
    void Init();

    namespace Reg
    {
        void SetLength(int num, uint length);
        void Write(int num, uint value);
    }

    extern PinIn  pinLIMIT;      // PE7  58
    extern PinOut pinA0_RG;      // PG5  90
    extern PinOut pinA1_RG;      // PG6  91
    extern PinOut pinA2_RG;      // PG3  89
    extern PinOut pinCLK_RG;     // PG7  92
    extern PinOut pinWR_RG;      // PG8  93
    extern PinOut pinDAT_RG;     // PD13 82
    extern Pin    pinST_TB;      // PF5  15
}
