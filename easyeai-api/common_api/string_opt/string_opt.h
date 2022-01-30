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

#ifndef STRING_OPERATION_H
#define STRING_OPERATION_H

#include <stdint.h>

#if defined(__cplusplus)
extern "C" {
#endif

extern uint32_t hexToi(const char *str);
extern void     val_to_hexStr(void *dst_pStr, int src_Val, int bit_num);
extern uint64_t read_val_from_str(char *buff, const char *strTitle);

#if defined(__cplusplus)
}
#endif
#endif // STRING_OPERATION_H