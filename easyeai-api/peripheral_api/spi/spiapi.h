/**
 *
 * Copyright 2021 by Guangzhou Easy EAI Technologny Co.,Ltd.
 * website: www.easy-eai.com
 *
 * Author: CHM <chenhaiman@easy-eai.com>
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * License file for more details.
 * 
 */

#ifndef SPIAPI_H
#define SPIAPI_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#include <linux/spi/spidev.h>

int spi_transfer(int bus, int select, uint8_t const *tx, uint8_t const *rx, size_t len);
int spi_init(int bus, int select, uint32_t mode, uint8_t bits, uint32_t speed, uint16_t delay);
void spi_exit(int bus, int select);

#ifdef __cplusplus
}
#endif
#endif
