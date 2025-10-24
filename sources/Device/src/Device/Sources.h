// 2025/10/24 08:54:26 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Hardware/HAL/HAL_PINS.h"


// XP10 - Источник U 50 V

namespace Source50V
{
    void Init();

    void Update();

    extern PinOut pin50EP;
    extern PinOut pin50EN;
}


// XP13 - Источник 3 кВ

namespace Source3kV
{
    extern PinOut pinENRGV; // Разрешение регистра источника напряжения 3кВ
}
