/**
 *
 * Copyright 2021 by Guangzhou Easy EAI Technologny Co.,Ltd.
 * website: www.easy-eai.com
 *
 * Author: Jiehao.Zhong <zhongjiehao@easy-eai.com>
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * License file for more details.
 * 
 */

 
#ifndef __DATA_CHECK_H__
#define __DATA_CHECK_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// md5:
extern char *create_md5_code(const char *type, const char *content);

// BCC (异或校验)
extern uint8_t block_check_character(uint8_t *hexData, int length);

// check sum
//   对称校验：
extern uint8_t check_sum_check(uint8_t *hexData, uint16_t length);
//   非对称校验：
extern uint8_t TX_CheckSum(uint8_t *buf, uint8_t len);
extern uint8_t RX_CheckSum(uint8_t *buf, uint8_t len);

// CRC (循环冗余)
extern uint8_t CRC_8(uint8_t *hexData, uint16_t length);
extern uint16_t CRC_16(uint8_t *hexData, uint16_t length);

#ifdef __cplusplus
}
#endif

#endif