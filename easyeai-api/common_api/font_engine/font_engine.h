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

#ifndef FONT_ENGINE_H
#define FONT_ENGINE_H

#include <stdint.h>

#if defined(__cplusplus)
extern "C" {
#endif

typedef struct {
	uint8_t Alpha;
	uint8_t Red;
	uint8_t Green;
	uint8_t Bule;
}FontColor;

extern int32_t font_engine_init(char *fontLib, char *charSet);
extern int32_t font_engine_set_fontSize(uint32_t fontSize);
extern int32_t font_engine_putText(uint8_t *imgData, uint32_t imgWidth, uint32_t imgHeight, char *text, uint32_t posX, uint32_t posY, FontColor color);
extern int32_t font_engine_unInit();

extern int32_t gbk_to_utf8(const char *gbkStr, char *utf8Str, int32_t bufLen);
extern int32_t utf8_to_gbk(const char *utf8Str, char *gbkStr, int32_t bufLen);

#if defined(__cplusplus)
}
#endif

#endif