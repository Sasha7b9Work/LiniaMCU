// 2025/08/30 18:39:38 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Hardware/HAL/HAL_PINS.h"
#include <stm32f4xx_hal.h>


PinOut pB_3_50_V(Port::_G, Pin::_11);
PinOut pB_END1B(Port::_C, Pin::_3);
PinOut pB_END2B(Port::_C, Pin::_2);
PinOut pB_ENRGB(Port::_C, Pin::_1);


PinOut pS_END1P(Port::_C, Pin::_0);
PinOut pS_END2P(Port::_F, Pin::_10);
PinOut pS_ENRGP(Port::_F, Pin::_9);

PinOut pMEAS_I_SPEED(Port::_G, Pin::_11);
PinOut pMEAS_I_ENRGI(Port::_F, Pin::_1);

PinOut pRAZV_ENDU(Port::_C, Pin::_15);
PinOut pRAZV_ENRGF(Port::_F, Pin::_0);

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

PinOut pSOURCE_3kV_ENRGV(Port::_F, Pin::_8);

PinIn  pFPGA_LIMIT(Port::_E, Pin::_7);
PinOut pFPGA_A0_RG(Port::_G, Pin::_5);
PinOut pFPGA_A1_RG(Port::_G, Pin::_6);
PinOut pFPGA_A2_RG(Port::_G, Pin::_3);
PinOut pFPGA_CLK_RG(Port::_G, Pin::_7);
PinOut pFPGA_WR_RG(Port::_G, Pin::_8);
PinOut pFPGA_DAT_RG(Port::_D, Pin::_13);        // \todo Так ли это?
//Pin    pFPGA_ST_TB;      //      15

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

    Commutator::pin3000VE.Init();
    Commutator::pin200EN.Init();
    Commutator::pin200EP.Init();
    Commutator::pin20EN.Init();
    Commutator::pin20EP.Init();
    Commutator::pinENRGK.Init();
}
