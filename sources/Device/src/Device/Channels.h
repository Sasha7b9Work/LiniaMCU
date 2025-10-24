// 2025/10/24 09:30:11 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Hardware/HAL/HAL_PINS.h"


// Интерфейсы трёх блоков каналов

// Канал базы
namespace ChanB
{
    extern PinOut pin3_50_V;        // Определяет режим высокого напряжения/режим большого тока
    extern PinOut pinEND1B;         // Разрешение DAC
    extern PinOut pinEND2B;         // Разрешение DAC
    extern PinOut pinENRGB;         // Разрешение регистра
}


// XP5 - Канал подложки
namespace ChanS
{
    extern PinOut pinEND1P;         // Разрешение DAC
    extern PinOut pinEND2P;         // Разрешение DAC
    extern PinOut pinENRGP;         // Разрешение регистра
}


// XP6, XP7 - Измеритель тока, формирователь развёртки (канал коллектора)
namespace ChanC
{
    extern PinOut pinRAZV_ENDU;       // Разрешение измерителя U блока развёртки
    extern PinOut pinRAZV_ENRGF;      // Разрешение регистра

    extern PinOut pinMEAS_I_ENRGI;    // Выбор регистра диапазона тока
    extern PinOut pinMEAS_I_SPEED;
}
