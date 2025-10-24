// 2025/10/24 08:56:42 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Hardware/HAL/HAL_PINS.h"


// XP12 - Коммутатор

namespace Commutator
{
    void Init();

    void Update();

    extern PinIn  pCOMM_3000VE;
    extern PinIn  pCOMM_200EN;
    extern PinIn  pCOMM_200EP;
    extern PinIn  pCOMM_20EN;
    extern PinIn  pCOMM_20EP;
}
