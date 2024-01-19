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

#ifndef NODE_DESC_H
#define NODE_DESC_H

#include <sys/types.h>

#include <stdint.h>
#include <stdbool.h>

//定义每个内存块的大小
#define     MEM_BLOCK_SIZE_5M               0x500000
#define     MEM_BLOCK_SIZE_2560K            0x280000
#define     MEM_BLOCK_SIZE_2304K            0x260000
#define     MEM_BLOCK_SIZE_2048K            0x200000
#define     MEM_BLOCK_SIZE_1024K            0x100000
#define     MEM_BLOCK_SIZE_512K             0x80000
#define     MEM_BLOCK_SIZE_256K             0x40000
#define     MEM_BLOCK_SIZE_128K             0x20000
#define     MEM_BLOCK_SIZE_64K              0x10000
#define     MEM_BLOCK_SIZE_32K              0x8000
#define     MEM_BLOCK_SIZE_4K               (4 * 1024)

#define     AAC_BITRATE_96K     96000
#define     AAC_BITRATE_64K     64000
#define     AAC_BITRATE_48K     48000
#define     AAC_BITRATE_32K     32000
#define     AAC_BITRATE_24K     24000
#define     AAC_BITRATE_16K     16000
#define     AAC_BITRATE_12K     12000
#define     AAC_BITRATE_8K      8000
#define     AAC_BITRATE_88200   88200
#define     AAC_BITRATE_44100   44100
#define     AAC_BITRATE_22050   22050
#define     AAC_BITRATE_11025   11025
#define     AAC_BITRATE_7350    7350

//解码帧压缩算法类型
typedef enum
{
    VDEC_CHN_FORMAT_H264 = 0,
    VDEC_CHN_FORMAT_MJPEG,
    VDEC_CHN_FORMAT_MPEG4,
    VDEC_CHN_FORMAT_H265,
} VDEC_CHN_FORMAT_E;

/*
 * G.711是国际电信联盟ITU-T定制出来的一套语音压缩标准，它代表了对数PCM（logarithmic pulse-code modulation）抽样标准，是主流的波形声音编解码标准，主要用于电话。
 *     1,主要用脉冲编码调制对音频采样，采样率为8k每秒。它利用一个 64Kbps 未压缩通道传输语音讯号。
 *     2,压缩率为1：2， 即把16位成8位。
 
 * G.711 标准下主要有两种压缩算法。
 *     1,u-law algorithm （又称u-law, ulaw, mu-law），主要运用于北美和日本。
 *     2,A-law algorithm，主要运用于欧洲和世界其他地区。特别设计用来方便计算机处理的。
 
 * G.711将14bit(uLaw)或者13bit(aLaw)采样的PCM数据编码成8bit的数据流，播放的时候在将此8bit的数据还原成14bit或者13bit进行播放，
   不同于MPEG这种对于整体或者一段数据进行考虑再进行编解码的做法，G711是波形编解码算法，就是一个sample对应一个编码，所以压缩比固定为：
 *     1,8/14 = 57% (uLaw)
 *     2,8/13 = 62% (aLaw)
 */
typedef enum
{
    ADEC_CHN_FORMAT_G711_A, //G.711 A律(PCMA)
    ADEC_CHN_FORMAT_G711_U, //G.711 μ律(PCMU)
    ADEC_CHN_FORMAT_G726,   //G.726
    ADEC_CHN_FORMAT_AAC_LATM, //AAC LATM封装
    ADEC_CHN_FORMAT_AAC_ADIF, //AAC ADIF封装
    ADEC_CHN_FORMAT_AAC_ADTS, //AAC ADTS封装
    ADEC_CHN_FORMAT_AAC_MPEG4_GENERIC, //AAC MPEG4 Generic(裸数据)
    ADEC_CHN_FORMAT_INVALID,
}
ADEC_CHN_FORMAT_E;

typedef struct
{
    uint32_t dwX;
    uint32_t dwY;
    uint32_t dwWidth;
    uint32_t dwHeight;
}VDIS_REGION_S;

typedef struct {
    uint32_t            dwSignalVout;  //解码通道ID
    VDEC_CHN_FORMAT_E   eVdecChnFormat;//编码类型(H.264/MPEG4...)
    uint8_t             bySubType;     //帧类型(1:I帧, 0:非I帧)
    uint8_t             byIsEOS;       //末帧标记
    uint32_t            dwFrameIndex;  // 帧序号
    uint32_t            dwHeight;
    uint32_t            dwWidth;
    uint32_t            dwTargetFrameRate;  //视频帧率
    VDIS_REGION_S       stVdisRegion;       //显示位置
    uint32_t            dwCropEnable;       //
    VDIS_REGION_S       stActRegion;        //有效区域
    uint64_t            ddwTimeStamp;       //时间戳，单位毫秒
    uint64_t            ddwReceiveTimeStamp;//帧接收时间，仅用于统计
    uint32_t            dwDataLen;          //帧长度
}VideoNodeDesc;

#define MAX_CONFIG_SIZE 64
typedef struct {
    uint32_t            dwStreamId;       //随机数，用于识别信号流
    ADEC_CHN_FORMAT_E   ePayloadType;
    uint32_t            dwFrameIndex;
    uint32_t            dwChannelNums;    //声道数，单声道，双声道，多声道
    uint32_t            dwSampleRateHz;   //采样率，单位Hz，例如48000
    uint32_t            dwBitRate;        //比特率，单位bps, 例如32、64、96、128、192kbps
    uint8_t             byAACHeader[10];  //如果【PayloadType】的值[是ADTS,这个就是ADTS头；是ADIF,这个就是ADIF头。]
    uint16_t            wAACHeaderLen;
    uint32_t            dwDataLen;
    uint64_t            ddwTimeStamp;
    uint16_t            wProfile;         // rtsp SDP profile
    int8_t              strConfig[MAX_CONFIG_SIZE + 1];  //rtsp SDP config
}AudioNodeDesc;


#endif // NODE_DESC_H
 
