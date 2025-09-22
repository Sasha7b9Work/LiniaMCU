// 2025/09/22 13:38:06 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Device/Device.h"
#include "Device/FPGA.h"
#include "Device/PCM.h"
#include "Device/Base.h"
#include "Device/Substrate.h"
#include "Device/MeasCurrent.h"
#include "Device/ScanFormer.h"
#include "Device/Source50V.h"
#include "Device/Source3kV.h"
#include "Device/Switch.h"


void Device::Init()
{
    FPGA::Init();
    PCM::Init();
    Base::Init();
    Substrate::Init();
    MeasCurrent::Init();
    ScanFormer::Init();
    Source50V::Init();
    Source3kV::Init();
    Switch::Init();
}

