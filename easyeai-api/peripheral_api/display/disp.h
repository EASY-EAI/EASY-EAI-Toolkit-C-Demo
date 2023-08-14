/**
 *
 * Copyright 2021 by Guangzhou Easy EAI Technologny Co.,Ltd.
 * website: www.easy-eai.com
 *
 * Author: CHM <chenhaiman@easy-eai.com>
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * License file for more details.
 * 
 */

#ifndef DISP_H
#define DISP_H

#ifdef __cplusplus
extern "C" {
#endif

#include "rkmedia/rkmedia_api.h"

typedef struct disp_win {
	int enable;
	int win_x;
	int win_y;
	int win_w;
	int win_h;
	int rotation;	//顺时针旋转输入图像角度，支持90、180、270、0度(若旋转和裁切搭配使用，处理顺序为先裁切后旋转)
	IMAGE_TYPE_E in_fmt;
	int in_w;		//输入图像宽度
	int in_h;		//输入图像高度
	int HorStride;	//输入图像水平步长
	int VirStride;	//输入图像垂直步长
	/* 如果不设置crop系列参数，则默认拉伸原图铺满整个win ;
	 *设置crop则先裁切再把裁切后的图像铺满整个win，以便保持图像宽高比例
	 */
	int crop_x;		//裁切起始X坐标(基于旋转前图像的坐标系)
	int crop_y;		//裁切起始Y坐标(基于旋转前图像的坐标系)
	int crop_w;		//裁切后的图像宽度(以旋转前的图像为参考)
	int crop_h;		//裁切后的图像高度(以旋转前的图像为参考)
} disp_win_t;

typedef struct disp_screen {
	int screen_x;
	int screen_y;
    int screen_width;
	int screen_height;
	disp_win_t wins[VMIX_MAX_CHN_NUM];
} disp_screen_t;

/* 公共api */
void disp_preset_uiLayer(int enable);

/* 适合初次使用 */
int disp_init(int width, int height); //默认输入BGR888
void disp_exit(void);
void disp_commit(void *ptr, int data_len);

/* pro */
int disp_init_pro(disp_screen_t *screen);
void disp_exit_pro(void);
void disp_commit_pro(void *ptr, int chn, int data_len);


#ifdef __cplusplus
}
#endif
#endif

