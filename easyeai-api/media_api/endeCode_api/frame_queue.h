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

#include "node_desc.h"

#if defined(__cplusplus)
extern "C" {
#endif

/*
 * 注意：
 * 1、本队列为H264、H265、AAC传输专用共享内存队列，不适合用作其他用途。
 * 2、本队列通过共享内存实现，因此在任意进程内，都为同一对象；只要通道号一样，无论在哪条进程，数据都会写入同一条通道。
 * 3、每一条进程都需要调用create_video_frame_queue_pool，进行内存在本进程的地址空间进行映射。
 * 4、本队列为循环队列，只用作数据缓冲。因此过快写入，解码不及时，同一条通道内的旧数据将会被覆盖。
 * 4.1、建议使用“完整未解码帧”的方式送入队列，若以“数据流”方式送入，则有丢帧风险。
 */

#define MAX_VIDEO_CHN_NUMBER 8
extern uint32_t create_video_frame_queue_pool(uint32_t channelNum);
extern uint32_t push_node_to_video_channel(uint32_t videoChnId, VideoNodeDesc *pNodeDesc, uint8_t *pbyFrameData);
extern uint32_t get_node_from_video_channel(uint32_t videoChnId, VideoNodeDesc *pNodeDesc, uint8_t *pbyFrameData);


extern uint32_t create_audio_frame_queue_pool(uint32_t channelNum);
extern uint32_t push_node_to_audio_channel(uint32_t audioChnId, AudioNodeDesc *pNodeDesc, uint8_t *pbyFrameData);
extern uint32_t get_node_from_audio_channel(uint32_t audioChnId, AudioNodeDesc *pNodeDesc, uint8_t *pbyFrameData);



#if defined(__cplusplus)
}
#endif
#endif // FRAME_QUEQUE_H

