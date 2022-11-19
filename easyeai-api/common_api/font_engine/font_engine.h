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

#include <stdbool.h>
#include <stdint.h>

#if defined(__cplusplus)
extern "C" {
#endif

#define CODE_UTF8 "utf8"
#define CODE_GBK  "gbk"

extern int32_t gbk_to_utf8(const char *gbkStr, char *utf8Str, int32_t bufLen);
extern int32_t gbk_to_unicode(const char *gbkStr, char *unicodeStr, int32_t bufLen);
extern int32_t utf8_strlen(const char *utf8Str);
extern int32_t utf8_to_gbk(const char *utf8Str, char *gbkStr, int32_t bufLen);
extern int32_t utf8_to_unicode(const char *utf8Str, char *uniCodeStr, int32_t uniCodeLen);

typedef struct {
	char fontLib[128];   // 字体 [*.ttf]
	char textCodec[64];  // 字符集 [utf8]
	uint32_t fontSize;   // 字体大小
}Font_t;

typedef struct {
	uint8_t Alpha;
	uint8_t Red;
	uint8_t Green;
	uint8_t Bule;
}FontColor;

extern int32_t global_font_create(const char *fontLib, const char *codec);
extern int32_t global_font_set_textCodec(const char *codec);
extern int32_t global_font_set_fontSize(uint32_t fontSize);
extern int32_t global_font_destory();
extern int32_t putText(uint8_t *imgData, uint32_t imgWidth, uint32_t imgHeight, const char *text, uint32_t posX, uint32_t posY, FontColor color);


#if defined(__cplusplus)
}
#endif

#endif