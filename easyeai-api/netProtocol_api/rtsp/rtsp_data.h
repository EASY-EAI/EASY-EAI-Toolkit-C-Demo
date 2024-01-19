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
    AUDIO_TYPE_G711_A, //G.711 A律(PCMA)
    AUDIO_TYPE_G711_U, //G.711 μ律(PCMU)
    AUDIO_TYPE_G726,   //G.726
    AUDIO_TYPE_AAC_ADTS, //AAC ADTS封装
    AUDIO_TYPE_AAC_MPEG4_GENERIC, //AAC MPEG4 Generic(裸数据)
    AUDIO_TYPE_INVALID,
} AUDIO_TYPE_E;

typedef struct {
    uint16_t        videoChnId;  //视频通道号
    VDEC_FORMAT_E   frameFormat; //帧格式
    uint8_t         frameType;   //帧类型(0:未知, 1:I帧, 2:P帧, 3:B帧)
    uint8_t         frameRate;   //帧率
    uint32_t        frameIndex;  //帧序号
    uint32_t        frameWidth;  //源画面宽度
    uint32_t        frameHeight; //源画面高度
    uint32_t        dataLen;     //帧数据长度
    uint64_t        timeStamp;   //pts播放时间戳，单位毫秒
    uint64_t        recTimeStamp;//接收时间戳，单位毫秒
}RTSPVideoDesc_t;

#define MAX_CONFIG_SIZE 64
typedef struct {
    uint16_t        audioChnId;  //音频通道号
    AUDIO_TYPE_E    frameFormat;
    uint32_t        frameIndex;
    uint32_t        channelNums; //声道数，单声道，双声道，多声道
    uint32_t        sampleRateHz;//采样率，单位Hz，例如8000
    uint32_t        bitRate;     //比特率，单位bps, 例如64000
    uint32_t        dataLen;     //帧数据长度
    uint64_t        timeStamp;   //pts播放时间戳，单位毫秒
    uint16_t        profile;     // rtsp SDP profile
    char            strConfig[MAX_CONFIG_SIZE + 1];  //rtsp SDP config
}RTSPAudioDesc_t;

// Client
//============
typedef	int32_t (*RtspClientVideoCB)(void *, RTSPVideoDesc_t *, uint8_t *);
typedef	int32_t (*RtspClientAudioCB)(void *, RTSPAudioDesc_t *, uint8_t *);
// ==========================================================================================


// Server
//============
typedef	void (*VideoConnect)(void *pCustomData);
typedef	int32_t (*VideoDataIn)(void *pCustomData, RTSPVideoDesc_t *, uint8_t *);
typedef struct {
    VDEC_FORMAT_E eDateFmt;
    VideoConnect pConnectHook;
    VideoDataIn pDataInHook;
    void *pCustomData;
}RtspServerVideoHooks;

typedef	void (*AudioConnect)(void *pCustomData);
typedef	int32_t (*AudioDataIn)(void *pCustomData, RTSPAudioDesc_t *, uint8_t *);
typedef struct {
    AUDIO_TYPE_E eDateFmt;
    AudioConnect pConnectHook;
    AudioDataIn pDataInHook;
    void *pCustomData;
}RtspServerAudioHooks;
// ==========================================================================================

#endif // RTSP_DATA_H

