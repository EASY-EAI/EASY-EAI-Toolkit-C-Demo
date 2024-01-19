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

#include <alsa/asoundlib.h>

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
    AUDIOCH_LAYOUT_DEFALUT = 0,
    AUDIOCH_LAYOUT_MONO,
    AUDIOCH_LAYOUT_STEREO,   ///< 立体声
    AUDIOCH_LAYOUT_2POINT1,
    AUDIOCH_LAYOUT_2_1,
    AUDIOCH_LAYOUT_SURROUND,
    AUDIOCH_LAYOUT_3POINT1,
    AUDIOCH_LAYOUT_4POINT0,
    AUDIOCH_LAYOUT_4POINT1,
    AUDIOCH_LAYOUT_2_2,
    AUDIOCH_LAYOUT_QUAD,
    AUDIOCH_LAYOUT_5POINT0,
    AUDIOCH_LAYOUT_5POINT1,
    AUDIOCH_LAYOUT_5POINT0_BACK,
    AUDIOCH_LAYOUT_5POINT1_BACK,
    AUDIOCH_LAYOUT_6POINT0,
    AUDIOCH_LAYOUT_6POINT0_FRONT,
    AUDIOCH_LAYOUT_HEXAGONAL,
    AUDIOCH_LAYOUT_6POINT1,
    AUDIOCH_LAYOUT_6POINT1_BACK,
    AUDIOCH_LAYOUT_6POINT1_FRONT,
    AUDIOCH_LAYOUT_7POINT0,
    AUDIOCH_LAYOUT_7POINT0_FRONT,
    AUDIOCH_LAYOUT_7POINT1,
    AUDIOCH_LAYOUT_7POINT1_WIDE,
    AUDIOCH_LAYOUT_7POINT1_WIDE_BACK,
    AUDIOCH_LAYOUT_OCTAGONAL,
    AUDIOCH_LAYOUT_HEXADECAGONAL,
    AUDIOCH_LAYOUT_STEREO_DOWNMIX,
    
    AUDIOCH_LAYOUT_NB
} AUDIO_CHANNEL_LAYOUT_E;

// =======================        [DeCode]        =======================
typedef struct {
    uint32_t channel;
    uint32_t buf_size;
    uint32_t frameIndex;
    uint32_t eos;
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
    uint32_t channel;       // 解码通道号
    uint32_t frameIndex;
    uint32_t err_info;
    uint32_t discard;
    int64_t pts;
    snd_pcm_format_t sample_fmt;
    int32_t arrangement;    // 音频数据的排列方式[0:交错排列 1:平面排列]
    int32_t aChannels;      // 音频通道数
    int32_t layout;         // 音频通通道布局(立体声、环绕声等)，暂时无作用
    int32_t sample_nb;      // 一帧音频数据中的音频样本个数
    int32_t sample_size;    // 一个音频样本所占的内存空间大小
    int32_t sample_rate;    // 音频采样率
    int32_t bufSize;        // 音频数据大小：bufSize = aChannels * sample_nb * sample_size;
      void *pBuf;
} AudioFrameData;

typedef	int32_t (*AudioFrameCB)(void *, AudioFrameData *);

extern int32_t create_decoder(uint32_t maxChnNum);

extern int32_t create_decMedia_channel(uint32_t *u32ChannelId);
extern int32_t close_decMedia_channel(uint32_t u32ChannelId);
extern int32_t set_decMedia_channel_callback(uint32_t u32ChannelId, VideoFrameCB pFunc, void *pRecObj);
extern int32_t push_node_in_decMedia_channel(uint32_t u32ChannelId, VideoNodeDesc *pNodeDesc, uint8_t *pData);
extern int32_t push_buff_in_decMedia_channel(uint32_t u32ChannelId, uint8_t *pData, VDEC_CHN_FORMAT_E vFmt, uint32_t dataLen, uint8_t isEOS, uint32_t fps);

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
    VDEC_CHN_FORMAT_E out_fmt;
    uint32_t out_fps;
    uint32_t width;
    uint32_t height;
    uint32_t hor_stride;   //stride:跨距
    uint32_t ver_stride;
}WorkPara;

// 编码器高级工作参数[非必须]
typedef struct {
    int32_t num_frames;     // WorkPara的out_fmt为VDEC_CHN_FORMAT_MJPEG时填1，其它情况均填0。
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
    int32_t rc_mode;        // 码率控制模式(可填:MPP_ENC_RC_MODE_CBR、MPP_ENC_RC_MODE_VBR、MPP_ENC_RC_MODE_AVBR、MPP_ENC_RC_MODE_FIXQP)
    int32_t bps_target;     // 目标码率(0:[根据width、height、fps_out_num、fps_out_den自动计算值], n:[使用n值])
    int32_t bps_max;        // 码率上限(0:[根据bps_target自动计算值], n:[使用n值])
    int32_t bps_min;        // 码率下限(0:[根据bps_target自动计算值], n:[使用n值])
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

// 音频编码器工作参数[必须]
typedef struct {
    AUDIO_CHANNEL_LAYOUT_E channel_layout; //声道布局
    bool                   bInterleaved;   //声道数据交错排列
    snd_pcm_format_t       sample_fmt;     //采样格式(输入格式)
    uint32_t               sample_rate;    //采样率
    ADEC_CHN_FORMAT_E      out_fmt;        //输出格式
    uint32_t               bit_rate;       //压缩比特率
}AudioWorkPara;

typedef	int32_t (*VideoStreamCB)(void *, VideoNodeDesc *, uint8_t *);
typedef	int32_t (*AudioStreamCB)(void *, AudioNodeDesc *, uint8_t *);


extern int32_t create_encoder(uint32_t maxChnNum);

extern int32_t create_encMedia_channel(int32_t *i32ChannelId);
extern int32_t close_encMedia_channel(int32_t i32ChannelId);
extern int32_t set_encMedia_channel_callback(int32_t i32ChannelId, VideoStreamCB pFunc, void *pRecObj);
extern int32_t set_encMedia_channel_workPara(int32_t i32ChannelId, WorkPara *wp, AdvanceWorkPara *awp);
extern int32_t push_frame_to_encMedia_channel(int32_t i32ChannelId, void *pData, uint32_t dataLen, uint8_t bIsEOS);
extern   void *map_inBuffer_from_encMedia_channel(int32_t i32ChannelId, size_t *maxbufSize);
extern int32_t commit_buffer_to_encMedia_channel(int32_t i32ChannelId, uint8_t bIsEOS);
extern int32_t request_encMedia_channel_outIFrame(int32_t i32ChannelId);


extern int32_t create_encMedia_audio_channel(int32_t *i32ChannelId);
extern int32_t close_encMedia_audio_channel(int32_t i32ChannelId);
extern int32_t set_encMedia_audio_channel_callback(int32_t i32ChannelId, AudioStreamCB pFunc, void *pRecObj);
extern int32_t set_encMedia_audio_channel_workPara(int32_t i32ChannelId, AudioWorkPara *wp);
extern int32_t push_frame_to_encMedia_audio_channel(int32_t i32ChannelId, void *pData, uint32_t dataLen);

#if defined(__cplusplus)
}
#endif


#endif
