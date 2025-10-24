// 2025/09/22 13:50:22 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Device/PCM/PCM.h"
#include "Utils/BufferOSDP.h"
#include "Hardware/HAL/HAL.h"
#include "Utils/String.h"
#include "Device/PCM/SCPI.h"


namespace PCM
{
    static BufferOSDP in_buffer(1024);

    static bool ProcessInputBuffer();
}


void PCM::Init()
{
}


void PCM::Update()
{
    HAL_USART1::GetData(in_buffer);

    while (!in_buffer.IsEmpty() && ProcessInputBuffer())
    {
    }
}


bool PCM::ProcessInputBuffer()
{
    int pos_begin = in_buffer.FirstPosition(':');

    int pos_end = in_buffer.FirstPosition('\0');

    if (pos_begin < 0)
    {
        return false;
    }

    if (pos_end < 0)
    {
        in_buffer.RemoveFirst(pos_begin);
        return false;
    }

    ParserPCM::Parse(in_buffer.Data(pos_begin));

    in_buffer.RemoveFirst(pos_end);

    return true;
}
