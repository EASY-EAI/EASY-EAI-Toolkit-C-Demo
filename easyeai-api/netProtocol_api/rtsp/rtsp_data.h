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

#ifndef RTSP_DATA_H
#define RTSP_DATA_H

#include <sys/types.h>

#include <stdint.h>
#include <stdbool.h>

//解码帧压缩算法类型
typedef enum
{
    VDEC_FORMAT_H264 = 0,
    VDEC_FORMAT_MJPEG,
    VDEC_FORMAT_MPEG4,
    VDEC_FORMAT_H265,
} VDEC_FORMAT_E;

typedef enum
{
    AUDIO_TYPE_G711_A, //G.711 A律
    AUDIO_TYPE_G711_U, //G.711 μ律
    AUDIO_TYPE_G726,   //G.726
    AUDIO_TYPE_AAC_ADTS, //AAC ADTS封装
    AUDIO_TYPE_AAC_MPEG4_GENERIC, //AAC MPEG4 Generic(裸数据)
    AUDIO_TYPE_INVALID,
} AUDIO_TYPE_E;

typedef struct {
    uint16_t        videoChnId;  //视频通道号
    VDEC_FORMAT_E   frameFormat; //帧格式
    uint8_t         frameType;   //帧类型(1:I帧, 0:非I帧)
    uint8_t         frameRate;   //帧率
    uint32_t        frameIndex;  //帧序号
    uint32_t        frameWidth;  //源画面宽度
    uint32_t        frameHeight; //源画面高度
    uint32_t        dataLen;     //帧数据长度
    uint64_t        timeStamp;   //编码输出时间戳，单位毫秒
    uint64_t        recTimeStamp;//接收时间戳，单位毫秒
}RTSPVideoDesc_t;

#define MAX_CONFIG_SIZE 64
typedef struct {
    AUDIO_TYPE_E    ePayloadType;
    uint32_t        dwStreamId;     //随机数，用于识别信号流
    uint32_t        dwSampleRateHz; //采样率，单位Hz，例如8000
    uint16_t        wProfile;       // rtsp SDP profile
    uint32_t        dwBitRate;      //比特率，单位bps, 例如64000
    uint64_t        ddwTimestamp;
    uint32_t        dwFrameIndex;
    int8_t          strConfig[MAX_CONFIG_SIZE + 1];  //rtsp SDP config
    uint32_t        dwDataLen;
}RTSPAudioDesc_t;

// Client
//============
typedef	int32_t (*RtspClientVideoCB)(void *, RTSPVideoDesc_t *, uint8_t *);
// ==========================================================================================


// Server
//============
typedef	void (*VideoConnect)();
typedef	int32_t (*VideoDataIn)(RTSPVideoDesc_t *, uint8_t *);
typedef struct {
    VideoConnect pConnectHook;
    VideoDataIn pDataInHook;
}RtspServerVideoHooks;

typedef	void (*AudioConnect)();
typedef	int32_t (*AudioDataIn)(RTSPAudioDesc_t *, uint8_t *);
typedef struct {
    AudioConnect pConnectHook;
    AudioDataIn pDataInHook;
}RtspServerAudioHooks;
// ==========================================================================================

#endif // RTSP_DATA_H

