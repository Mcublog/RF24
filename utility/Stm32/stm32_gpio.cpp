/**
 * @file stm32_gpio.cpp
 * @author Viacheslav (slava@ks2corp.com)
 * @brief
 * @version 0.1
 * @date 2022-02-10
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "stm32_gpio.hpp"

#include "gpio.h"

/**
 * @brief Set CE level
 *
 * @param level
 */
void stm32_write_ce(bool level)
{
    GPIO_PinState state = level ? GPIO_PIN_SET : GPIO_PIN_RESET;
    HAL_GPIO_WritePin(RF_CE_GPIO_Port, RF_CE_Pin, state);
}

/**
 * @brief Set CS level
 *
 * @param level
 */
void stm32_write_cs(bool level)
{
    GPIO_PinState state = level ? GPIO_PIN_SET : GPIO_PIN_RESET;
    HAL_GPIO_WritePin(RF_CS_GPIO_Port, RF_CS_Pin, state);
}
