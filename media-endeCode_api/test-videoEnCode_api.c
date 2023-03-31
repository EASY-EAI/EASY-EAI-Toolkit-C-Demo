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

#define SOURCE_FILE "./video.nv12"
#define OUTPUT_FILE "./output.264"
#define FRAME_WIDTH	    720
#define FRAME_HEIGHT	576
#define	IMGRATIO		1.5
#define	IMAGE_SIZE		(FRAME_WIDTH*FRAME_HEIGHT*IMGRATIO)

#define MAXCHNNUM 4

FILE *fp_output = NULL;
/* ======================== 编码好的NAL单元在此处输出 ======================== */
int32_t StreamOutpuHandle(void *obj, VideoNodeDesc *pNodeDesc, uint8_t *pNALUData)
{    
    //这里把一包包的nalu存起来
    printf("[Output] ------------- dataLen = %d\n", pNodeDesc->dwDataLen);
    if(fp_output){
        fwrite(pNALUData, 1, pNodeDesc->dwDataLen, fp_output);
    }

    return 0;
}

int main(void)
{
    int ret = 0, count = 0;

    // source file
    FILE *fp_input = NULL;
    char *pbuf = NULL;

    // encode
    WorkPara wp;
    //AdvanceWorkPara awp;
	
	uint32_t encodeChn_Id;
    create_encoder(MAXCHNNUM);
	create_encMedia_channel(&encodeChn_Id);
	if((0 <= encodeChn_Id) && (encodeChn_Id < MAXCHNNUM)){
		printf("encode channel create succ, channel Id = %u \n", encodeChn_Id);
	}else{
		printf("encode channel create faild !\n");
        goto exit3;
	}


    /* ============================ 初始化源视频文件 ============================ */
    fp_input = fopen(SOURCE_FILE, "r+b");
    if(NULL == fp_input){
		printf("open %s faild !\n", SOURCE_FILE);
		printf("    If %s is not exist, Please create it by run test-videoDeCode_api \n", SOURCE_FILE);
        goto exit3;
    }
    pbuf = (char *)malloc(IMAGE_SIZE);
    if(NULL == pbuf){
		printf("create input buffer faild !\n");
        goto exit2;
    }
    

    fp_output = fopen(OUTPUT_FILE, "w+b");
    /* ============================= 初始化编码通道 ============================= */
	set_encMedia_channel_callback(encodeChn_Id, StreamOutpuHandle, NULL);
    memset(&wp, 0, sizeof(WorkPara));
    wp.in_fmt  = VFRAME_TYPE_NV12;
    wp.out_fmt = VCODING_TYPE_AVC;
    wp.width   = FRAME_WIDTH;
    wp.height  = FRAME_HEIGHT;
    wp.out_fps = 25;
	ret = set_encMedia_channel_workPara(encodeChn_Id, &wp, NULL);
    if(ret){
        goto exit1;
    }

    /* ============================ 送帧进入编码通道 ============================= */
    while(1){
        if(0 < fread(pbuf, IMAGE_SIZE, 1, fp_input)){
            count++;    
            //printf("put [%03d] frame in enCoder ...\n", count);
        
    		push_frame_to_encMedia_channel(encodeChn_Id, pbuf, IMAGE_SIZE);
            usleep(10*1000);
        }else{
            usleep(100*1000);
            break;
        }
    }

    if(fp_output){
        fclose(fp_output);
        fp_output = NULL;
    }

    
    close_encMedia_channel(encodeChn_Id);

exit1:
    free(pbuf);
    pbuf = NULL;
    
exit2:
    if(fp_input){
        fclose(fp_input);
        fp_input = NULL;
    }
    
exit3:
    return ret;
}

