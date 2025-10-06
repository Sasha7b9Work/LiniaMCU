// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Hardware/HAL/HAL.h"
#include "Hardware/Timer.h"
#include "Device/Device.h"
#include <cstring>


static TimeMeterMS meter;


int main()
{
    HAL::Init();

    HAL_TIM::Delay(500);

    Device::Init();

    while (1)
    {
        static int i = 0;
        
        if (meter.ElapsedTime() > 100)
        {
            meter.Reset();

            static char message[3] = { 'H', 'i', '\0' };
            
            message[1] = 'i' + i;
            
            i++;
            
            if(i > 5)
            {
                i = 0;
            }
            
            HAL_USART1::Transmit(message, (int)std::strlen(message));
        }
    }
}
