// 2025/09/22 13:38:06 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Device/Device.h"
#include "Device/FPGA.h"
#include "Device/PCM/PCM.h"
#include "Hardware/HAL/HAL.h"
#include "Device/Sources.h"
#include "Device/Commutator.h"
#include "Hardware/Timer.h"


void Device::Init()
{
    Commutator::Init();

    Source50V::Init();

    FPGA::Init();

    PCM::Init();
}

    
void Device::Update()
{
    Commutator::Update();

    PCM::Update();
}
