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

#ifndef AUDIO_H
#define AUDIO_H

#ifdef __cplusplus
extern "C" {
#endif

#include <rkmedia/rkmedia_api.h>

int ao_init(SAMPLE_FORMAT_E fmt, int rate, int chn, int vol);
int ao_exit(void);
int ao_start(char *path);
int ao_stop(void);

int ai_init(SAMPLE_FORMAT_E fmt, int rate, int chn, int vol);
int ai_start(char * path);
int ai_exit(void);
int ai_stop(void);

#ifdef __cplusplus
}
#endif
#endif


