// 2025/08/30 18:39:38 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Hardware/HAL/HAL_PINS.h"


PinOut pB_3_50_V(Port::_G, Pin::_11);
PinOut pB_END1B(Port::_C, Pin::_3);
PinOut pB_END2B(Port::_C, Pin::_2);
PinOut pB_ENRGB(Port::_C, Pin::_1);


PinOut pS_END1P(Port::_C, Pin::_0);
PinOut pS_END2P(Port::_F, Pin::_10);
PinOut pS_ENDRGP(Port::_F, Pin::_9);

PinOut pMEAS_I_SPEED(Port::_G, Pin::_11);
//PinOut pMEAS_I_ENRGI(Port)

PinOut pRAZV_ENDU(Port::_C, Pin::_15);
PinOut pRAZV_ENRGF(Port::_F, Pin::_0);

PinOut pSOURCE_50V_50EP(Port::_A, Pin::_6);
PinOut pSOURCE_50V_50EN(Port::_F, Pin::_11);

PinIn  pCOMM_3000VE(Port::_C, Pin::_4);
PinIn  pCOMM_200EN(Port::_C, Pin::_5);
PinIn  pCOMM_200EP(Port::_B, Pin::_0);
PinIn  pCOMM_20EN(Port::_B, Pin::_1);
PinIn  pCOMM_20EP(Port::_B, Pin::_2);
PinOut pCOMM_ENRGK(Port::_F, Pin::_7);

PinOut pin_SOURCE_3kV_ENRGV(Port::_F, Pin::_8);

PinIn  pFPGA_LIMIT(Port::_E, Pin::_7);
PinOut pFPGA_A0_RG(Port::_G, Pin::_5);
PinOut pFPGA_A1_RG(Port::_G, Pin::_6);
PinOut pFPGA_A2_RG(Port::_G, Pin::_3);
PinOut pFPGA_CLK_RG(Port::_G, Pin::_7);
PinOut pFPGA_WR_RG(Port::_G, Pin::_8);
//Pin    pFPGA_DAT_RG(Port::_D, Pin::_13);
//Pin    pFPGA_ST_TB;      //      15

PinOut pPI_ENB_STM(Port::_D, Pin::_12);
//Pin    pPI_TX;           // PB6  136
//Pin    pPI_RX;           // PA10 102

PinOut pDAT1_DAC(Port::_D, Pin::_8);
PinOut pCLK1_DAC(Port::_D, Pin::_11);

PinOut pDAT2_DAC(Port::_B, Pin::_15);
PinOut pCLK2_DAC(Port::_D, Pin::_9);
