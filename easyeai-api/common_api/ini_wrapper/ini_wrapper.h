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

 
#ifndef __INI_WRAPPER_H__
#define __INI_WRAPPER_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

extern int32_t ini_read_int(const char *file, const char *pcSection, const char *pcKey, int *pVal);
extern int32_t ini_read_string(const char *file, const char *pcSection, const char *pcKey, char *pcStr, int len);
extern int32_t ini_write_int(const char *file, const char *pcSection, const char *pcKey, int Val);
extern int32_t ini_write_string(const char *file, const char *pcSection, const char *pcKey, const char *pcStr);

#ifdef __cplusplus
}
#endif

#endif


