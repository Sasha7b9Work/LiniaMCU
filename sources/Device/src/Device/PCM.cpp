// 2025/09/22 13:50:22 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Device/PCM.h"
#include "Utils/Buffer.h"
#include "Hardware/HAL/HAL.h"


namespace PCM
{
    static Buffer in_buffer(1024);
}


void PCM::Init()
{
}


void PCM::Update()
{
    HAL_USART1::GetData(in_buffer);
}
