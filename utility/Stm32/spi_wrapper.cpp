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
#include "stm32_gpio.hpp"
#include "FreeRTOS.h"
#include "task.h"
#include "log_libs.h"
#include "rtos_libs.h"

/**
 * @brief Construct a new SPI::SPI object
 *
 */
SPI::SPI()
{
    this->transfer_type = TxRxTransfer;
    this->task_handle = xTaskGetCurrentTaskHandle();
    LOG_INFO("%d", task_handle);
}

/**
 * @brief Destroy the SPI::SPI object
 *
 */
SPI::~SPI(){};

/**
 * Transfer a single byte
 * @param tx_ Byte to send
 * @return Data returned via spi
 */
uint8_t SPI::transfer(uint8_t tx_)
{
    uint8_t data_rx = 0;
    this->transfer_type = RxOnly;
    // HAL_SPI_TransmitReceive(&hspi1, &tx_, &data_rx, 1, 10);
    HAL_SPI_TransmitReceive_DMA(&hspi1, reinterpret_cast<uint8_t *>(&tx_), &data_rx, 1);
    FRTOS_TaskNotifyWaitBit(portMAX_DELAY);
    if FRTOS_TaskNotifyTakeBit(1<<static_cast<int>(RxOnly));
        return data_rx;
    return 0;
}

/**
 * Transfer a buffer of data
 * @param tbuf Transmit buffer
 * @param rbuf Receive buffer
 * @param len Length of the data
 */
void SPI::transfernb(char* tbuf, char* rbuf, uint32_t len)
{
    this->transfer_type = RxOnly;
    //HAL_SPI_TransmitReceive(&hspi1, reinterpret_cast<uint8_t *>(tbuf), reinterpret_cast<uint8_t *>(rbuf), len, 10);
    HAL_SPI_TransmitReceive_DMA(&hspi1, reinterpret_cast<uint8_t *>(tbuf), reinterpret_cast<uint8_t *>(rbuf), len);
    FRTOS_TaskNotifyWaitBit(portMAX_DELAY);
    if FRTOS_TaskNotifyTakeBit(1<<static_cast<int>(RxOnly));
        return;
}

/**
 * Transfer a buffer of data without an rx buffer
 * @param buf Pointer to a buffer of data
 * @param len Length of the data
 */
void SPI::transfern(char* buf, uint32_t len)
{
    this->transfer_type = TxOnly;
    // HAL_SPI_Transmit(&hspi1, reinterpret_cast<uint8_t *>(buf), len, 10);
    HAL_SPI_Transmit_DMA(&hspi1, reinterpret_cast<uint8_t *>(buf), len);
    FRTOS_TaskNotifyWaitBit(portMAX_DELAY);
    if FRTOS_TaskNotifyTakeBit(1<<static_cast<int>(TxOnly));
        return;
}

/**
 * @brief Sending notify to task with SPI instance
 *
 * @param notify
 * @param taskWokenP
 */
void SPI::send_spi_notify_from_irq(TransferType_t notify, void *taskWokenP)
{
    xTaskNotifyFromISR(reinterpret_cast<TaskHandle_t>(this->task_handle),
                       1 << static_cast<int>(notify),
                       eSetBits,
                       reinterpret_cast<BaseType_t *>(taskWokenP));
}

/**
 * @brief Get the transfer type object
 *
 * @return TransferType
 */
TransferType_t SPI::get_transfer_type()
{
    return this->transfer_type;
}