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

    extern PinIn  pinLIMIT;
    extern PinOut pinA0_RG;
    extern PinOut pinA1_RG;
    extern PinOut pinA2_RG;
    extern PinOut pinCLK_RG;
    extern PinOut pinWR_RG;
    extern PinOut pinDAT_RG;
    extern Pin    pinST_TB;
}
