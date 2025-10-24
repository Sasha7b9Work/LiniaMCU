// 2025/10/24 08:56:42 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Hardware/HAL/HAL_PINS.h"


// XP12 - Коммутатор

namespace Commutator
{
    void Init();

    void Update();

    extern PinIn  pin3000VE;
    extern PinIn  pin200EN;
    extern PinIn  pin200EP;
    extern PinIn  pin20EN;
    extern PinIn  pin20EP;
    extern PinOut pinENRGK;
}
