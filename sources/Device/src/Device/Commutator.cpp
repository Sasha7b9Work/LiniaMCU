// 2025/10/24 08:56:33 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Device/Commutator.h"
#include "Device/PCM/SCPI.h"


namespace Commutator
{
    static StructPinIn pins[] =
    {
        { &pin3000VE, "3000V" },
        { &pin200EN,  "200N" },
        { &pin200EP,  "200P" },
        { &pin20EP,   "20P" },
        { &pin20EN,   "20N" },
        { nullptr,    nullptr }
    };
}


void Commutator::Update()
{
    StructPinIn *pin = &pins[0];

    while (pin->pin)
    {
        bool prev_state = pin->pin->PrevState();
        bool state = pin->pin->Get();

        if (prev_state != state)
        {
            SCPI::Send("PININ:%s:STATE %d", pin->name, state ? "1" : "0");
        }
        
        pin++;
    }
}
