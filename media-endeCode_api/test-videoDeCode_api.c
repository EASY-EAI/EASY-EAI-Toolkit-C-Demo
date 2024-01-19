#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <aio.h>

#include "endeCode_api.h"

#include "mpp_mem.h"

#define PHOTO_FILE "./photo.nv12"
#define VIDEO_FILE "./video.nv12"

static struct aiocb g_wd = {0};
static int g_VideoFd = -1;
// 由于保存录像文件不能堵塞解码帧输出，因此需要异步写入文件
int saveOneFrameInVideo(void *pData, uint32_t dataLen)
{
    if(g_VideoFd < 0){
	    g_VideoFd = open(VIDEO_FILE, O_CREAT|O_WRONLY, 0755);
        bzero(&g_wd,sizeof(g_wd));
        g_wd.aio_fildes = g_VideoFd;
        g_wd.aio_offset = 0;
    }
    
	if(g_VideoFd < 0){
		printf("file<%s> open error \n", VIDEO_FILE);
		return -1;
	}

    // 由于这里是直接写入，没有针对pts的处理，因此含有B帧的码流，视频会出现跳帧现象。
    g_wd.aio_buf = pData;
    g_wd.aio_nbytes =  dataLen;
    if(aio_write(&g_wd) < 0){
		printf("file<%s> write error \n", VIDEO_FILE);
		return -1;
	}
    g_wd.aio_offset += dataLen;

	return 0;
}
int saveOneFrameInPhoto(void *pData, uint32_t dataLen)
{
	FILE *fp = fopen (PHOTO_FILE, "wb");
	if(NULL == fp){
		printf("file<%s> open error \n", PHOTO_FILE);
		return -1;
	}	
	if(1 != fwrite(pData, dataLen, 1, fp)){
		printf("file<%s> write error \n", PHOTO_FILE);
		return -1;
	}	
	fclose(fp);
	return 0;
}

void readFrameToDecodeQueue(uint32_t chnId, const char *filename)
{
    bool loop_flag = false; //如果loop_flag为true,则是无限循环解码方式
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
						if (true == loop_flag) {
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
				//成功取流，送流进入解码器的输入队列
				push_buff_in_decMedia_channel(chnId, (uint8_t *)pBuf, VDEC_CHN_FORMAT_H264, dataLen, (uint8_t)bIsEndOfStream, 25);
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
	printf("[frame][%03d] -- [stride[width x height]] = [%u x %u[%u x %u]], pts[%lld] size = %u\n", frame_count, 
        pFrame->hor_stride, pFrame->ver_stride, 
        pFrame->width, pFrame->height, 
        pFrame->pts,
        pFrame->buf_size);
    
	if(250 == frame_count){
		// 可用该命令播放：mplayer -demuxer rawvideo -rawvideo w=720:h=576:format=nv12 pic.nv12 -loop 0
		saveOneFrameInPhoto(pFrame->pBuf, pFrame->buf_size);
	}
    saveOneFrameInVideo(pFrame->pBuf, pFrame->buf_size);
	return 0;
}

int main(int argc, char* argv[])
{
	int32_t count = 20;
	uint32_t channel = 0;
	
	if(argc < 2){
		printf("\n");
		printf("please select a file, example:\n");
		printf("    ./test-videoDeCode_api tc10.264\n");
		printf("\n");
		return -1;
	}
	
	// 1.创建解码器
	create_decoder(8);
	
	// 2.向解码器申请解码通道
	if(0 == create_decMedia_channel(&channel)){
		printf("create channel OK, chn = %u\n", channel);
		
		// 3.往成功申请的通道绑定解码输出处理函数
		set_decMedia_channel_callback(channel, VideoFrameHandle, NULL);

        //sleep(2);
		// 4.从文件读入数据
		readFrameToDecodeQueue(channel, argv[1]);
		
		// 5.等待一段时间[建议20s以上，否则解码尚未结束就销毁通道了]后，关闭解码通道
		//     异步IO写入数据到文件比较耗时，这里给予时间充分等待
		while(1){
			if(count <= 0)
				break;

		    printf("count down %d ...\n", count);
			sleep(1);
			count--;
		}
		
		frame_count = 0;
		printf("close channel ...\n");
		close_decMedia_channel(channel);
	}
    
    while(aio_error(&g_wd) != 0) {
        usleep(100*1000);
    }
    printf("\nVideo file Asynchronous Write Complete, framsize = %d\n", aio_return(&g_wd));

    if(0 < g_VideoFd){
        close(g_VideoFd);
    }

	return 0;
}
