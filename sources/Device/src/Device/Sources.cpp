// 2025/10/24 08:54:16 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Device/Sources.h"
#include "Hardware/HAL/HAL_PINS.h"


namespace Source50V
{
    static PinOut pin50EP(Port::_A, Pin::_6);      // 42
    static PinOut pin50EN(Port::_F, Pin::_11);     // 49
}


void Source50V::Init()
{
    pin50EP.Init();
    pin50EN.Init();
}
