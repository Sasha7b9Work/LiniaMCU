// 2025/09/22 13:50:22 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Device/PCM/PCM.h"
#include "Utils/BufferOSDP.h"
#include "Hardware/HAL/HAL.h"
#include "Utils/String.h"


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
    int pos_begin = in_buffer.FirstPosition(':');

    int pos_end = in_buffer.FirstPosition('\0');

    if (pos_begin < 0)
    {
        return;
    }

    if (pos_end < 0)
    {
        in_buffer.RemoveFirst(pos_begin);
        return;
    }

    String message{ in_buffer.Data(pos_begin) };        // Теперь в message принятое сообщение



    in_buffer.RemoveFirst(pos_end);
}
