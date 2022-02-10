/**
 * @file spi.cpp
 * @author Viacheslav (slava.k@ks2corp.com)
 * @brief
 * @version 0.1
 * @date 2022-02-10
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "spi_wrapper.hpp"

#include "spi.h"
#include "stm32f4xx_hal.h"

/**
 * Transfer a single byte
 * @param tx_ Byte to send
 * @return Data returned via spi
 */
uint8_t SPI::transfer(uint8_t tx_)
{
    auto hspiP = GetSpiHandle();
    uint8_t data_rx = 0;
    HAL_SPI_TransmitReceive(hspiP, &tx_, &data_rx, 1, 10);
    return data_rx;
}

/**
 * Transfer a buffer of data
 * @param tbuf Transmit buffer
 * @param rbuf Receive buffer
 * @param len Length of the data
 */
void SPI::transfernb(char* tbuf, char* rbuf, uint32_t len)
{
    auto hspiP = GetSpiHandle();
    HAL_SPI_TransmitReceive(hspiP, reinterpret_cast<uint8_t *>(tbuf), reinterpret_cast<uint8_t *>(rbuf), len, 10);
}

/**
 * Transfer a buffer of data without an rx buffer
 * @param buf Pointer to a buffer of data
 * @param len Length of the data
 */
void SPI::transfern(char* buf, uint32_t len)
{
    auto hspiP = GetSpiHandle();
    HAL_SPI_Transmit(hspiP, reinterpret_cast<uint8_t *>(buf), len, 10);
}

void chipSelect(bool mode)
{

}