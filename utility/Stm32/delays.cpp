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

#include "tim.h"
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
    __HAL_TIM_SET_COUNTER(&htim14, 0);  // set the counter value a 0
    while (__HAL_TIM_GET_COUNTER(&htim14) < microseconds);  // wait for the counter to reach the us input in the parameter
}

unsigned int stm32_millis(void)
{
    return HAL_GetTick();
}
