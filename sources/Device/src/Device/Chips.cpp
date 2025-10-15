// 2025/10/15 16:04:55 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Device/Chips.h"


ChipDAC dacs[10] =
{
    { nullptr, nullptr, nullptr },  // Формирователь развёртки и измеритель напряжения
    { nullptr, nullptr, nullptr },  // Формирователь развёртки и измеритель напряжения
    { nullptr, nullptr, nullptr },  // Источник-измеритель (канал базы)
    { nullptr, nullptr, nullptr },  // Источник-измеритель (канал базы)
    { nullptr, nullptr, nullptr },  // Источник-измеритель (дополнительный канал)
    { nullptr, nullptr, nullptr },  // Источник-измеритель (дополнительный канал)
    { nullptr, nullptr, nullptr },  // Источник напряжения 50 В
    { nullptr, nullptr, nullptr },
    { nullptr, nullptr, nullptr },
    { nullptr, nullptr, nullptr }
};


ChipADC adcs[10] =
{
    { nullptr, nullptr, nullptr },  // Формирователь развёртки и измеритель напряжения
    { nullptr, nullptr, nullptr },  // Источник-измеритель (канал базы)
    { nullptr, nullptr, nullptr },  // Источник-измеритель (дополнительный канал)
    { nullptr, nullptr, nullptr },  // Измеритель тока
    { nullptr, nullptr, nullptr },
    { nullptr, nullptr, nullptr },
    { nullptr, nullptr, nullptr },
    { nullptr, nullptr, nullptr },
    { nullptr, nullptr, nullptr },
    { nullptr, nullptr, nullptr }
};


ChipREG regs[10] =
{
    { &pin_SOURCE_3kV_ENRGV, nullptr, nullptr },  // Источник напряжения 3000В
    { &pCOMM_ENRGK,          nullptr, nullptr },  // Коммутатор
    { &pRAZV_ENRGF,          nullptr, nullptr },  // Формирователь развёртки и измеритель напряжения
    { &pB_END2B,             nullptr, nullptr },  // Источник-измеритель (канал базы)
    { &pS_ENDRGP,            nullptr, nullptr },  // Источник-измеритель (дополнительный канал)
    { &pMEAS_I_ENRGI,        nullptr, nullptr },  // Измеритель тока
    { &pSOURCE_50V_50EN,     nullptr, nullptr },  // Источник напряжения 50 В
    { nullptr,               nullptr, nullptr },
    { nullptr,               nullptr, nullptr },
    { nullptr,               nullptr, nullptr }
};
