// 2025/10/15 16:04:55 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Device/Chips.h"


//--- Блок базы 


namespace Chips
{
    namespace ADC
    {
        static uint lengths[10];
    }
}


void Chips::ADC::SetLength(int num_chip, uint length)
{
    lengths[num_chip] = length;
}


void Chips::ADC::Write(int num_chip, uint value)
{

}
