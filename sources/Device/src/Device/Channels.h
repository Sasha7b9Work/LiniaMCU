// 2025/10/24 09:30:11 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Hardware/HAL/HAL_PINS.h"


// Интерфейсы трёх блоков каналов

// Канал базы
namespace ChanB
{

}


// Канал подложки
namespace ChanP
{

}


// Канал коллектора
namespace ChanC
{
    extern PinOut pinMEAS_I_ENRGI;    // Выбор регистра диапазона тока
    extern PinOut pinRAZV_ENDU;       // Разрешение измерителя U блока развёртки
    extern PinOut pinRAZV_ENRGF;      // Разрешение регистра
}
