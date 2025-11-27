// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Hardware/HAL/HAL.h"
#include "Device/Commutator.h"
#include "Device/Sources.h"
#include "Device/FPGA.h"
#include "Device/PCM/PCM.h"
#include "Device/Device.h"


int main()
{
    HAL::Init();

    HAL_TIM::Delay(500);

    Device::Init();

    FPGA::Init();

    while (true)
    {
        PCM::Update();

        Device::Update();
    }
}
