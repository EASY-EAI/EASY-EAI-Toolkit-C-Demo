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
#define     MEM_BLOCK_SIZE_5M            	0x500000
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

//解码帧压缩算法类型
typedef enum
{
    VDEC_CHN_FORMAT_H264 = 0,
    VDEC_CHN_FORMAT_MJPEG,
    VDEC_CHN_FORMAT_MPEG4,
    VDEC_CHN_FORMAT_H265,
} VDEC_CHN_FORMAT_E;

typedef enum
{
    AUDIO_PAYLOAD_TYPE_G711_A, //G.711 A律
    AUDIO_PAYLOAD_TYPE_G711_U, //G.711 μ律
    AUDIO_PAYLOAD_TYPE_G726,   //G.726
    AUDIO_PAYLOAD_TYPE_AAC_ADTS, //AAC ADTS封装
    AUDIO_PAYLOAD_TYPE_AAC_MPEG4_GENERIC, //AAC MPEG4 Generic(裸数据)
    AUDIO_PAYLOAD_TYPE_INVALID,
}
AUDIO_PAYLOAD_TYPE_E;

typedef	struct
{
	uint32_t dwX;
	uint32_t dwY;
	uint32_t dwWidth;
	uint32_t dwHeight;
}VDIS_REGION_S;

typedef struct {
    uint32_t            dwSignalVout;  //解码通道ID
    VDEC_CHN_FORMAT_E   eVdecChnFormat;//编码类型(H.264/MPEG4...)
    uint8_t             bySubType;     //帧类型(1:I, 0:P, 2:B)
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
    AUDIO_PAYLOAD_TYPE_E ePayloadType;
    uint32_t            dwStreamId;     //随机数，用于识别信号流
    uint32_t            dwSampleRateHz; //采样率，单位Hz，例如8000
    uint16_t            wProfile;       // rtsp SDP profile
    uint32_t            dwBitRate;      //比特率，单位bps, 例如64000
    uint64_t            ddwTimestamp;
    uint32_t            dwFrameIndex;
    int8_t              strConfig[MAX_CONFIG_SIZE + 1];  //rtsp SDP config
    uint32_t            dwDataLen;
}AudioNodeDesc;


#endif // NODE_DESC_H

