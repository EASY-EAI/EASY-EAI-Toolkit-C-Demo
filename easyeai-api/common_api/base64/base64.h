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

 
#ifndef BASE64_H
#define BASE64_H

#include <stdint.h>


#if defined(__cplusplus)
extern "C" {
#endif

//注意：一般编码后的数据，比编码前的数据至少要多1/3，具体大小为输入数据大小以3对齐后的4/3
//比如：
//	输入数据长度为2，以3对齐后，则为3，再*4/3
extern int32_t base64_encode(char *out_data, const char* in_data, unsigned int in_len);
extern int32_t base64_decode(char *out_data, unsigned int out_len, const char* encoded_string);

#if defined(__cplusplus)
}
#endif
#endif // BASE64_H