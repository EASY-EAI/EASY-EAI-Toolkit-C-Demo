 /**
 *
 * Copyright 2023 by Guangzhou Easy EAI Technologny Co.,Ltd.
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
#ifndef WAV_OPT_H
#define WAV_OPT_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "wav_info.h"

extern int32_t wav_rOpen(const char *filePath, wav_info *pWavInfo);
extern int32_t wav_wOpen(const char *filePath, wav_info *pWavInfo);
extern int32_t wav_close(int32_t fd);


#ifdef __cplusplus
}
#endif
#endif
