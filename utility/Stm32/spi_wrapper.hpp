/**
 * @file spi.h
 * Class declaration for SPI helper files
 */

/**
 * Example of spi.h class declaration for SPI portability
 *
 * @defgroup Porting_SPI Porting: SPI
 *
 * @{
 */
#pragma once

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "stm32_types.h"
#ifndef DOXYGEN_FORCED
// exclude this line from the docs to prevent displaying in the list of classes
class SPI
#endif
{
public:

	/**
	 * SPI constructor
	 */
	SPI();

	/**
	 * Start SPI
	 */
	void begin(int busNo);

	/**
	 * Transfer a single byte
	 * @param tx_ Byte to send
	 * @return Data returned via spi
	 */
	uint8_t transfer(uint8_t tx_);

	/**
	 * Transfer a buffer of data
	 * @param tbuf Transmit buffer
	 * @param rbuf Receive buffer
	 * @param len Length of the data
	 */
	void transfernb(char* tbuf, char* rbuf, uint32_t len);

	/**
	 * Transfer a buffer of data without an rx buffer
	 * @param buf Pointer to a buffer of data
	 * @param len Length of the data
	 */
	void transfern(char* buf, uint32_t len);

	/**
	 * @brief Unblock task with spi class from IRQ
	 *
	 */
	void send_spi_notify_from_irq(TransferType_t notify, void *taskWokenP);

	TransferType_t get_transfer_type();

#ifndef DOXYGEN_FORCED
// exclude this line from the docs to prevent warnings docs generators
	~ SPI();
#endif
private:

	/** Default SPI device */
	const char *device;
	void *task_handle;
	/** SPI Mode set */
	uint8_t mode;
	/** word size*/
	uint8_t bits;
	/** Set SPI speed*/
	uint32_t speed;
	int fd;

	TransferType_t transfer_type;

	void init();
};

/**@}*/
