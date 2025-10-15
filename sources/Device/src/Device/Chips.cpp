// 2025/10/15 16:04:55 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Device/Chips.h"


/*
+   ENRGV   // Регистр Источник 3 кВ
+   END1B   // DAC Канал B
+   END2B   //
+   ENRGB   // Регистр Канал B
+   END1P   // DAC Канала S
+   END2P   //
+   ENRGP   // Регистр Канал S
+   ENRGI   // Регистр измерителя тока
+   ENDU    // Формирователь развёртки
+   ENRGF   // Регистр формирователя
+   ENRGK   // Регистр коммутатора
*/


ChipDAC dacs[10] =
{   //      cs           clk         dat
    { 12, nullptr,     nullptr,    nullptr    },  // Канал C. Управляется с PCM
    { 12, &pRAZV_ENDU, &pCLK2_DAC, &pDAT2_DAC },  // Канал C. Диапазон
    { 12, &pB_END1B,   &pCLK1_DAC, &pDAT1_DAC },  // Канал B
    { 12, &pB_END2B,   &pCLK1_DAC, &pDAT1_DAC },  // Канал B
    { 12, &pS_END1P,   &pCLK1_DAC, &pDAT1_DAC },  // Канал S
    { 12, &pS_END2P,   &pCLK1_DAC, &pDAT1_DAC },  // Канал S
    { 12, nullptr,     nullptr,    nullptr    },  // Источник 50 В. Управляется с PCM
    { 0,  nullptr,     nullptr,    nullptr    },
    { 0,  nullptr,     nullptr,    nullptr    },
    { 0,  nullptr,     nullptr,    nullptr    }
};


ChipREG regs[10] =
{
    { 24, &pSOURCE_3kV_ENRGV, &pCLK2_DAC, &pDAT2_DAC },  // Источник 3кВ
    { 16, &pCOMM_ENRGK,       &pCLK2_DAC, &pDAT2_DAC },  // Коммутатор
    { 32, &pRAZV_ENRGF,       &pCLK2_DAC, &pDAT2_DAC },  // Канал C
    { 32, &pB_ENRGB,          &pCLK1_DAC, &pDAT1_DAC },  // Канал B
    { 32, &pS_ENRGP,          &pCLK1_DAC, &pDAT1_DAC },  // Канал S
    { 16, &pMEAS_I_ENRGI,     &pCLK2_DAC, &pDAT2_DAC },  // Измеритель тока
    { 0,  nullptr,            nullptr,    nullptr },
    { 0,  nullptr,            nullptr,    nullptr },
    { 0,  nullptr,            nullptr,    nullptr },
    { 0,  nullptr,            nullptr,    nullptr }
};


void ChipDAC::Write(uint value)
{
    clk->ToLow();

    cs->ToLow();

    for (int bit = (int)length - 1; bit >= 0; bit--)
    {
        clk->ToLow();

        dat->Set(_GET_BIT(value, bit) != 0);

        clk->ToHi();
    }

    cs->ToHi();

    clk->ToLow();
}
