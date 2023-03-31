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

#include "node_desc.h"

#if defined(__cplusplus)
extern "C" {
#endif

// =======================        [Common]        =======================
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
  VCODING_TYPE_UNKNOW = 0,
  VCODING_TYPE_AutoDetect,
  VCODING_TYPE_MPEG2,
  VCODING_TYPE_H263,
  VCODING_TYPE_MPEG4,
  VCODING_TYPE_WMV,
  VCODING_TYPE_RV,
  VCODING_TYPE_AVC,                 /* H.264 */
  VCODING_TYPE_MJPEG,
  VCODING_TYPE_VP8,
  VCODING_TYPE_VP9,
  VCODING_TYPE_VC1,
  VCODING_TYPE_FLV1,
  VCODING_TYPE_DIVX3,
  VCODING_TYPE_VP6,
  VCODING_TYPE_HEVC,                /* H.265 */
  VCODING_TYPE_AVSPLUS,
  VCODING_TYPE_AVS,
  VCODING_TYPE_KhronosExtensions,
  VCODING_TYPE_VendorStartUnused,
  
  VCODING_TYPE_BUTT
} VEDIO_CODING_TYPE_E;

typedef enum {
  AFRAME_TYPE_UNKNOW = 0,
  AFRAME_TYPE_WAV,

  AFRAME_TYPE_BUTT
} AUDIO_FRAME_TYPE_E;

// =======================        [DeCode]        =======================
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

extern int32_t create_decoder(uint32_t maxChnNum);

extern int32_t create_decMedia_channel(uint32_t *u32ChannelId);
extern int32_t close_decMedia_channel(uint32_t u32ChannelId);
extern int32_t set_decMedia_channel_callback(uint32_t u32ChannelId, VideoFrameCB pFunc, void *pRecObj);
extern int32_t push_node_in_decMedia_channel(uint32_t u32ChannelId, VideoNodeDesc *pNodeDesc, uint8_t *pData);
extern int32_t push_buff_in_decMedia_channel(uint32_t u32ChannelId, uint8_t *pData, VDEC_CHN_FORMAT_E vFmt, uint32_t dataLen, uint8_t isEOS);

extern int32_t create_decMedia_audio_channel(uint32_t *u32ChannelId);
extern int32_t close_decMedia_audio_channel(uint32_t u32ChannelId);
extern int32_t set_decMedia_audio_channel_callback(uint32_t u32ChannelId, AudioFrameCB pFunc, void *pRecObj);
extern int32_t push_node_in_decMedia_audio_channel(uint32_t u32ChannelId, AudioNodeDesc *pNodeDesc, uint8_t *pData);

    
// =======================        [EnCode]        =======================
typedef enum {
    RC_MODE_VBR,
    RC_MODE_CBR,
    RC_MODE_FIXQP,
    RC_MODE_AVBR,
    RC_MODE_BUTT
} EncRcMode;

// 编码器工作参数[必须]
typedef struct {
    VEDIO_FRAME_TYPE_E in_fmt;
    VEDIO_CODING_TYPE_E out_fmt;
    uint32_t out_fps;
    uint32_t width;
    uint32_t height;
    uint32_t hor_stride;   //stride:步长
    uint32_t ver_stride;
}WorkPara;

// 编码器高级工作参数[非必须]
typedef struct {
    int32_t num_frames;
    /* gop:I帧间隔 */
    int32_t gop_mode;       // 高级GOP模式，默认不需要配置(填0)
    int32_t gop_len;        // (0:[I帧间隔采用2*fps_out_num], n:[I帧间隔为n(1==n,即每一帧都是I帧)])
    int32_t vi_len;
    /* fps_out:输出帧率 */
    int32_t fps_out_flex;   // (0:[固定的输出帧率, 输出帧率=(fps_out_num/fps_out_den)], 1:[可变的输出帧率,完成帧编码后马上输出])
    int32_t fps_out_num;    // (0:[使用默认值], n:[使用n值]) -- 默认值为30
    int32_t fps_out_den;    // (0:[使用默认值], n:[使用n值]) -- 默认值为1
    /* fps_in :输入帧率 */
    int32_t fps_in_flex;    // (0:[固定的输入帧率, 输入帧率=(fps_in_num/fps_in_den)], 1:[可变的输入帧率])
    int32_t fps_in_num;     // (0:[使用默认值], n:[使用n值]) -- 默认值为30
    int32_t fps_in_den;     // (0:[使用默认值], n:[使用n值]) -- 默认值为1
    /* bps:码率 */
    int32_t rc_mode;        // 码率控制模式(CBR、VBR、AVBR、FIXQP)
    int32_t bps_target;     // 目标码率(CBR模式下使用)
    int32_t bps_max;        // 码率上限(VBR模式下使用)
    int32_t bps_min;        // 码率下限(VBR模式下使用)
    /* slice */
    uint32_t split_mode;    // slice 切分模式(0:[不切分], 1:[根据slice大小], 2:[根据宏块或CTU个数切分])
    uint32_t split_arg;
    uint32_t split_out;
    /* 以下参数可无须理会 */
    uint32_t osd_enable;   //osd:水印
    uint32_t osd_mode;
    uint32_t user_data_enable;
    uint32_t roi_enable;
}AdvanceWorkPara;

typedef	int32_t (*VideoStreamCB)(void *, VideoNodeDesc *, uint8_t *);
typedef	int32_t (*AudioStreamCB)(void *, AudioNodeDesc *, uint8_t *);


extern int32_t create_encoder(uint32_t maxChnNum);

extern int32_t create_encMedia_channel(uint32_t *u32ChannelId);
extern int32_t close_encMedia_channel(uint32_t u32ChannelId);
extern int32_t set_encMedia_channel_callback(uint32_t u32ChannelId, VideoStreamCB pFunc, void *pRecObj);
extern int32_t set_encMedia_channel_workPara(uint32_t u32ChannelId, WorkPara *wp, AdvanceWorkPara *awp);
extern int32_t push_frame_to_encMedia_channel(uint32_t u32ChannelId, void *pData, uint32_t dataLen);
    
//extern int32_t create_encMedia_audio_channel(uint32_t *u32ChannelId);
//extern int32_t close_encMedia_audio_channel(uint32_t u32ChannelId);
//extern int32_t set_encMedia_audio_channel_callback(uint32_t u32ChannelId, AudioStreamCB pFunc, void *pRecObj);

#if defined(__cplusplus)
}
#endif


#endif
