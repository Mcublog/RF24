/**
 * @file delays.cpp
 * @author Viacheslav (slava.k@ks2corp.com)
 * @brief
 * @version 0.1
 * @date 2022-02-10
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "delays.hpp"

#include "stm32f4xx_hal.h"
/**
 * @brief
 *
 * @param ms
 */
void stm32_delay_ms(int ms)
{
    HAL_Delay(ms);
}

/**
 * @brief
 *
 * @param microseconds
 */
void stm32_delay_us(int microseconds)
{
    // TODO: add implementation
}

unsigned int stm32_millis(void)
{
    return HAL_GetTick();
}
