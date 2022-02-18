#include <sys/time.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "frame_queue.h"
#include "endeCode_api.h"

#include "mpp_mem.h"

void readFrameToDecodeQueue(uint32_t chnId, const char *filename)
{
    RK_S32 frame_num = 0; //如果frame_num小于0,则是无限循环解码方式
	bool bIsEndOfStream = false;
	FILE *pFileinput_fp = NULL;
    size_t fileBuf_size  = MEM_BLOCK_SIZE_256K;

	// 1.打开文件
    pFileinput_fp = fopen(filename, "rb");
    if (NULL == pFileinput_fp) {
        printf("failed to open input file %s\n", filename);
		return ;
    }
	
	// 2.创建文件缓存
	char *pBuf = NULL;
	uint32_t dataLen = 0;
	pBuf = mpp_malloc(char, fileBuf_size);
	if (NULL == pBuf) {
		perror("video_dec_test malloc file stream buffer failed\n");
	}
	
	// 3.取码流
	if(pFileinput_fp){
		
		while(1){
			if(!bIsEndOfStream){
				do{
					// when packet size is valid read the input binary file
					if (fileBuf_size)
						dataLen = fread(pBuf, 1, fileBuf_size, pFileinput_fp);

					/*  取数据异常*/
					if (!fileBuf_size || dataLen != fileBuf_size || feof(pFileinput_fp)) {
						if (frame_num < 0) {
							clearerr(pFileinput_fp);	//清除ferror（fp）的返回值
							rewind(pFileinput_fp);		//让文件内部指针回到文件开头
							bIsEndOfStream = false;	//码流未结束
							printf("loop again\n");
						} else {
							// setup eos flag
							bIsEndOfStream = true;	//码流已结束
							printf("[FileCapturer] : found last packet\n");
							break;
						}
					}
				} while (!dataLen);/*取出数据为0, 重新取*/
			}else{
				break;
			}

			if(dataLen){
				//成功取流，送流进入  解码器的输入队列
				push_buff_to_video_channel(chnId, (uint8_t *)pBuf, dataLen, (uint8_t)bIsEndOfStream);
			}
		}
		// 4.取流完毕关闭文件
		fclose(pFileinput_fp);
	}
	// 5.释放缓存
	mpp_free(pBuf);
}


static int frame_count = 0;
int32_t VideoFrameHandle(void *pRecObj, VideoFrameData *pFrame)
{
	frame_count++;
	printf("[frame][%d] -- [width x height] = %u x %u, size = %u\n", frame_count, pFrame->width, pFrame->height, pFrame->buf_size);
	return 0;
}

int main(int argc, char* argv[])
{
	int32_t count = 3;
	uint32_t channel = 0;
	
	if(argc < 2){
		printf("\n");
		printf("please select a file, example:\n");
		printf("    ./test-videoDeCode_api tc10.264\n");
		printf("\n");
		return -1;
	}
	
	// 获取文件解码类型
    MppCodingType type = MPP_VIDEO_CodingAVC;
	//name_to_coding_type(argv[1], &type);
	
	// 1.创建解码器
	create_decoder(8);
	
	// 2.向解码器申请解码通道
	if(0 == create_decMedia_channel(&channel, type)){
		printf("create channel OK, chn = %u\n", channel);
		
		// 3.往成功申请的通道绑定解码输出处理函数
		set_decMedia_channel_callback(channel, VideoFrameHandle, NULL);
		
		// 4.从文件读入数据
		readFrameToDecodeQueue(channel, argv[1]);
		
		// 5.等待一段时间后，关闭解码通道
		while(1){
			if(count <= 0)
				break;
			
			sleep(1);
			count--;
		}
		
		frame_count = 0;
		printf("close channel ...\n");
		close_decMedia_channel(channel);
	}

	return 0;
}
