// 2025/10/15 16:04:55 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Device/Chips.h"


//--- Блок базы 


namespace Chips
{
    static int lengths[32];
}


void Chips::SetLength(int num_chip, int length)
{
    lengths[num_chip] = length;
}


void Chips::Write(int num_chip, uint value)
{

}
