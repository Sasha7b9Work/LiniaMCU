// 2025/08/30 18:39:38 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Hardware/HAL/HAL_PINS.h"
#include <stm32f4xx_hal.h>


namespace ChanB
{
    PinOut pin3_50_V(Port::_G, Pin::_11);   // 57
    PinOut pinEND1B(Port::_C, Pin::_3);     // 29
    PinOut pinEND2B(Port::_C, Pin::_2);     // 28
    PinOut pinENRGB(Port::_C, Pin::_1);     // 27
}


namespace ChanS
{
    PinOut pinEND1P(Port::_C, Pin::_0);     // 26
    PinOut pinEND2P(Port::_F, Pin::_10);    // 22
    PinOut pinENRGP(Port::_F, Pin::_9);     // 21
}


namespace ChanC
{
    PinOut pinRAZV_ENDU(Port::_C, Pin::_15);      //  9
    PinOut pinRAZV_ENRGF(Port::_F, Pin::_0);      // 10

    PinOut pinMEAS_I_ENRGI(Port::_F, Pin::_1);    // 11
    PinOut pinMEAS_I_SPEED(Port::_G, Pin::_11);   // 126
}


namespace Source50V
{
    PinOut pin50EP(Port::_A, Pin::_6);      // 42
    PinOut pin50EN(Port::_F, Pin::_11);     // 49
}


namespace Commutator
{
    PinIn  pin3000VE(Port::_C, Pin::_4);     // 44
    PinIn  pin200EN(Port::_C, Pin::_5);      // 45
    PinIn  pin200EP(Port::_B, Pin::_0);      // 46
    PinIn  pin20EN(Port::_B, Pin::_1);       // 47
    PinIn  pin20EP(Port::_B, Pin::_2);       // 48
    PinOut pinENRGK(Port::_F, Pin::_7);      // 19
}


namespace Source3kV
{
    PinOut pinENRGV(Port::_F, Pin::_8);     // 20
}


namespace FPGA
{
    PinIn  pinLIMIT(Port::_E, Pin::_7);               // 58
    PinOut pinA0_RG(Port::_G, Pin::_5);               // 90
    PinOut pinA1_RG(Port::_G, Pin::_6);               // 91
    PinOut pinA2_RG(Port::_G, Pin::_3);               // 89
    PinOut pinCLK_RG(Port::_G, Pin::_7);              // 92
    PinOut pinWR_RG(Port::_G, Pin::_8);               // 93
    PinOut pinDAT_RG(Port::_D, Pin::_13);             // 82    \todo Так ли это?
    Pin    pinST_TB(Port::_F, Pin::_5, PinMode::In);  // 15    \todo Так ли это?
}


PinOut pPI_ENB_STM(Port::_D, Pin::_12);
//Pin    pPI_TX;           // PB6  136
//Pin    pPI_RX;           // PA10 102

PinOut pDAT1_DAC(Port::_D, Pin::_8);
PinOut pCLK1_DAC(Port::_D, Pin::_11);

PinOut pDAT2_DAC(Port::_B, Pin::_15);
PinOut pCLK2_DAC(Port::_D, Pin::_9);


Pin::Pin(Port::E _port, Pin::E _pin, PinMode::E _mode)
{
    static GPIO_TypeDef *ports[Port::Count] =
    {
        GPIOA,
        GPIOB,
        GPIOC,
        GPIOD,
        GPIOE,
        GPIOF,
        GPIOG,
        GPIOH,
        GPIOI
    };

    port = ports[_port];

    static const uint16 pins[Pin::Count] =
    {
        GPIO_PIN_0,
        GPIO_PIN_1,
        GPIO_PIN_2,
        GPIO_PIN_3,
        GPIO_PIN_4,
        GPIO_PIN_5,
        GPIO_PIN_6,
        GPIO_PIN_7,
        GPIO_PIN_8,
        GPIO_PIN_9,
        GPIO_PIN_10,
        GPIO_PIN_11,
        GPIO_PIN_12,
        GPIO_PIN_13,
        GPIO_PIN_14,
        GPIO_PIN_15
    };

    pin = pins[_pin];

    mode = _mode;
}


void Pin::Init()
{

}


void PinIn::Init()
{
    Pin::Init();

    prev_state = Get();
}


bool PinIn::Get()
{
    GPIO_PinState state = HAL_GPIO_ReadPin((GPIO_TypeDef *)port, pin);

    prev_state = (state != GPIO_PIN_RESET);

    return prev_state;
}


bool PinIn::PrevState() const
{
    return prev_state;
}


void PinOut::Set(bool value)
{
    HAL_GPIO_WritePin((GPIO_TypeDef *)port, pin, value ? GPIO_PIN_SET : GPIO_PIN_RESET);
}


void PinOut::ToLow()
{
    Set(false);
}


void PinOut::ToHi()
{
    Set(true);
}


void HAL_PINS::Init()
{
    Source50V::pin50EN.Init();
    Source50V::pin50EP.Init();

    Source3kV::pinENRGV.Init();

    Commutator::pin3000VE.Init();
    Commutator::pin200EN.Init();
    Commutator::pin200EP.Init();
    Commutator::pin20EN.Init();
    Commutator::pin20EP.Init();
    Commutator::pinENRGK.Init();

    FPGA::pinLIMIT.Init();
    FPGA::pinA0_RG.Init();
    FPGA::pinA1_RG.Init();
    FPGA::pinA2_RG.Init();
    FPGA::pinCLK_RG.Init();
    FPGA::pinWR_RG.Init();
    FPGA::pinDAT_RG.Init();
    FPGA::pinST_TB.Init();

    ChanB::pin3_50_V.Init();
    ChanB::pinEND1B.Init();
    ChanB::pinEND2B.Init();
    ChanB::pinENRGB.Init();

    ChanS::pinEND1P.Init();
    ChanS::pinEND2P.Init();
    ChanS::pinENRGP.Init();

    ChanC::pinRAZV_ENDU.Init();
    ChanC::pinRAZV_ENRGF.Init();
    ChanC::pinMEAS_I_ENRGI.Init();
    ChanC::pinMEAS_I_SPEED.Init();
}
