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

#if defined(__cplusplus)
extern "C" {
#endif

typedef enum {
  VFRAME_TYPE_UNKNOW = 0,
  VFRAME_TYPE_GRAY8,
  VFRAME_TYPE_GRAY16,
  VFRAME_TYPE_YUV420P,
  VFRAME_TYPE_NV12,
  VFRAME_TYPE_NV21,
  VFRAME_TYPE_YV12,     /* YVU420P*/
  VFRAME_TYPE_FBC2,
  VFRAME_TYPE_FBC0,
  VFRAME_TYPE_YUV422P,
  VFRAME_TYPE_NV16,
  VFRAME_TYPE_NV61,
  VFRAME_TYPE_YV16,     /* YVU422P*/
  VFRAME_TYPE_YUYV422,
  VFRAME_TYPE_UYVY422,
  VFRAME_TYPE_RGB332,
  VFRAME_TYPE_RGB565,
  VFRAME_TYPE_BGR565,
  VFRAME_TYPE_RGB888,
  VFRAME_TYPE_BGR888,
  VFRAME_TYPE_ARGB8888,
  VFRAME_TYPE_ABGR8888,
  VFRAME_TYPE_JPEG,

  VFRAME_TYPE_BUTT
} VEDIO_FRAME_TYPE_E;

typedef enum {
  AFRAME_TYPE_UNKNOW = 0,
  AFRAME_TYPE_WAV,

  AFRAME_TYPE_BUTT
} AUDIO_FRAME_TYPE_E;

typedef struct {
    uint32_t channel;
    uint32_t buf_size;
    uint32_t frameIndex;
    uint32_t width;
    uint32_t height;
    uint32_t hor_stride;
    uint32_t ver_stride;
    uint32_t err_info;
    uint32_t discard;
    int64_t pts;
    VEDIO_FRAME_TYPE_E fmt;
    void *pBuf;
} VideoFrameData;

typedef	int32_t (*VideoFrameCB)(void *, VideoFrameData *);

typedef struct {
    uint32_t channel;
    uint32_t frameIndex;
    uint32_t buf_size;
    uint32_t err_info;
    uint32_t discard;
    int64_t pts;
    AUDIO_FRAME_TYPE_E fmt;
    void *pBuf;
} AudioFrameData;

typedef	int32_t (*AudioFrameCB)(void *, AudioFrameData *);

// =======================        [DeCode]        =======================
extern int32_t create_decoder(uint32_t maxChnNum);

extern int32_t create_decMedia_channel(uint32_t *u32ChannelId);
extern int32_t close_decMedia_channel(uint32_t u32ChannelId);
extern int32_t set_decMedia_channel_callback(uint32_t u32ChannelId, VideoFrameCB pFunc, void *pRecObj);

    
//extern int32_t create_decMedia_audio_channel(uint32_t *u32ChannelId);
//extern int32_t close_decMedia_audio_channel(uint32_t u32ChannelId);
//extern int32_t set_decMedia_audio_channel_callback(uint32_t u32ChannelId, AudioFrameCB pFunc, void *pRecObj);

    
// =======================        [EnCode]        =======================

#if defined(__cplusplus)
}
#endif


#endif
