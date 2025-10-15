// 2025/09/22 13:50:22 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Device/PCM.h"
#include "Utils/BufferOSDP.h"
#include "Hardware/HAL/HAL.h"


namespace PCM
{
    static BufferOSDP in_buffer(1024);

    static void ProcessInputBuffer();
}


void PCM::Init()
{
}


void PCM::Update()
{
    HAL_USART1::GetData(in_buffer);

    ProcessInputBuffer();
}


void PCM::ProcessInputBuffer()
{
    while (!in_buffer.IsEmpty() && in_buffer[0] != ':')
    {
        in_buffer.RemoveFirst(1);
    }

    if (in_buffer.IsEmpty())
    {
        return;
    }


}
