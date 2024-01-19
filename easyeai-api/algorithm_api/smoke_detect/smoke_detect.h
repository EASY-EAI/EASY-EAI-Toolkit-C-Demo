#ifndef SMOKE_DETECT_H
#define SMOKE_DETECT_H

#include "smoke_postprocess.h"
#include "rknn_api.h"
#include <opencv2/opencv.hpp>




/* 
 * 抽烟检测初始化函数
 * ctx:输入参数,rknn_context句柄
 * path:输入参数,算法模型路径
 */
int smoke_detect_init(rknn_context *ctx, const char * path);


/* 
 * 抽烟检测执行函数
 * ctx:输入参数,rknn_context句柄
 * input_image:输入参数,图像数据输入(cv::Mat是Opencv的类型)
 * output_dets:输出参数，目标检测框输出
 */
int smoke_detect_run(rknn_context ctx, cv::Mat input_image, smoke_detect_result_group_t *detect_result_group);


/* 
 * 抽烟检测释放函数
 * ctx:输入参数,rknn_context句柄
 */
int smoke_detect_release(rknn_context ctx);




#endif
