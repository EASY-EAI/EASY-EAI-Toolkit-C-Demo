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

#ifndef DECODE_MEDIA_H
#define DECODE_MEDIA_H

#include <sys/types.h>

#include <stdint.h>
#include <stdbool.h>

#include "mpp_frame.h"


#if defined(__cplusplus)
extern "C" {
#endif

typedef struct {
	int64_t pts;
	uint32_t frameIndex;
	uint32_t width;
	uint32_t height;
	uint32_t hor_stride;
	uint32_t ver_stride;
	uint32_t buf_size;
    uint32_t err_info;
    uint32_t discard;
    MppMeta meta;
    MppBuffer pBuf;
	MppFrameFormat fmt;
} VideoFrameData;

typedef	int32_t (*VideoFrameCB)(void *, VideoFrameData *);

typedef struct {
	int64_t pts;
	uint32_t width;
	uint32_t height;
	uint32_t hor_stride;
	uint32_t ver_stride;
	uint32_t buf_size;
    uint32_t err_info;
    uint32_t discard;
    MppMeta meta;
    MppBuffer pBuf;
	MppFrameFormat fmt;
} AudioFrameData;

typedef	int32_t (*AudioFrameCB)(void *, AudioFrameData *);

// =======================        [DeCode]        =======================
extern int32_t create_decoder(uint32_t maxChnNum);

extern int32_t create_decMedia_channel(uint32_t *u32ChannelId, MppCodingType type);
extern int32_t close_decMedia_channel(uint32_t u32ChannelId);
extern int32_t set_decMedia_channel_callback(uint32_t u32ChannelId, VideoFrameCB pFunc, void *pRecObj);

    
extern int32_t create_decMedia_audio_channel(uint32_t *u32ChannelId);
extern int32_t close_decMedia_audio_channel(uint32_t u32ChannelId);
extern int32_t set_decMedia_audio_channel_callback(uint32_t u32ChannelId, AudioFrameCB pFunc, void *pRecObj);

    
// =======================        [EnCode]        =======================

#if defined(__cplusplus)
}
#endif


#endif
