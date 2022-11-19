#ifndef _MOVING_DETECT_H_
#define _MOVING_DETECT_H_

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp> 

using namespace cv;
using namespace std;

#define MOVING_NUMB_MAX_SIZE 100

typedef struct _MOVING_BOX_RECT
{
	int left;
	int right;
	int top;
	int bottom;
} MOVING_BOX_RECT;

typedef struct _moving_detect_result_group_t
{
	int count;
	MOVING_BOX_RECT results[MOVING_NUMB_MAX_SIZE];
} moving_detect_result_group_t;


/* 
 * 移动检测函数
 * first_frame:输入参数,  图像帧1
 * second_frame:输入参数, 图像帧2
 * p_moving_detect_result:输出参数, 移动目标
 * obj_size_threshold:输入参数, 图像大小
 */
int moving_detect(Mat frame1, Mat frame2, moving_detect_result_group_t *p_moving_detect_result, unsigned int obj_size_threshold);


#endif
