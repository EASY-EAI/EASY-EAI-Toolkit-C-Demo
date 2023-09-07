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

#ifndef FRAME_QUEQUE_H
#define FRAME_QUEQUE_H

#include <sys/types.h>

#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>

#include "node_desc.h"

#if defined(__cplusplus)
extern "C" {
#endif

/*
 * 注意：
 * 1、本队列为H264、H265、AAC传输专用共享内存队列，不适合用作其他用途。
 * 2、本队列通过共享内存实现，因此在任意进程内，都为同一对象；只要通道号一样，无论在哪条进程，数据都会写入同一条通道。
 * 3、每一条进程都需要调用create_video_frame_queue_pool，进行内存在本进程的地址空间进行映射。
 * 4、本队列只用作数据缓冲。因此过快写入，解码不及时，会因队列被写满，新的数据无法写入而丢帧。
 * 4.1、建议使用“完整未解码帧”的方式送入队列，若以“数据流”方式送入，则有丢帧风险。
 * 5、9500-9600的key_t已被本队列占用。用户若另外有使用共享内存的需求，应避免与本队列的key冲突。
 */

#define MAX_VIDEO_CHN_NUMBER 8
extern int32_t create_video_frame_queue_pool(uint32_t channelNum);
extern bool    video_channel_is_empty(uint32_t videoChnId);
extern int32_t flush_video_channel(uint32_t videoChnId);
extern int32_t push_node_to_video_channel(uint32_t videoChnId, VideoNodeDesc *pNodeDesc, uint8_t *pFrameData);
extern int32_t push_buff_to_video_channel(uint32_t videoChnId, uint8_t *pFrameData, VDEC_CHN_FORMAT_E vFmt, uint32_t u32DataLen, uint8_t u8IsEOS);
extern int32_t get_node_from_video_channel(uint32_t videoChnId, VideoNodeDesc *pNodeDesc, uint8_t *pFrameData);


extern int32_t create_audio_frame_queue_pool(uint32_t channelNum);
extern bool    audio_channel_is_empty(uint32_t audioChnId);
extern int32_t flush_audio_channel(uint32_t audioChnId);
extern int32_t push_node_to_audio_channel(uint32_t audioChnId, AudioNodeDesc *pNodeDesc, uint8_t *pFrameData);
extern int32_t get_node_from_audio_channel(uint32_t audioChnId, AudioNodeDesc *pNodeDesc, uint8_t *pFrameData);



#if defined(__cplusplus)
}
#endif
#endif // FRAME_QUEQUE_H

