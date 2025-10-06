// 2025/10/06 11:10:16 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Hardware/HAL/HAL.h"
#include <stm32f4xx_hal.h>


namespace HAL_USART1
{
    static UART_HandleTypeDef h =
    {
        USART1,
        {
            115200,
            UART_WORDLENGTH_8B,
            UART_STOPBITS_1,
            UART_PARITY_NONE,
            UART_MODE_TX_RX,
            UART_HWCONTROL_NONE,
            UART_OVERSAMPLING_16
        }
    };

    void *handle = &h;
}


void HAL_USART1::Init()
{
    GPIO_InitTypeDef GPIO_InitStruct = { 0 };

    GPIO_InitStruct.Pin = GPIO_PIN_10;                  // RX
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_6;                   // TX
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART1_IRQn);

    if (HAL_UART_Init(&h) != HAL_OK)
    {
        ERROR_HANDLER();
    }
}


void HAL_USART1::Transmit(const void *buffer, int size)
{
    HAL_UART_Transmit(&h, (const uint8 *)buffer, (uint16)size, 100);
}


void USART1_IRQHandler(void)
{
    HAL_UART_IRQHandler((UART_HandleTypeDef *)HAL_USART1::handle);
}
