#ifndef SITE_SAFETY_H
#define SITE_SAFETY_H

#include "site_safety_postprocess.h"
#include "rknn_api.h"
#include <opencv2/opencv.hpp>




/* 
 * 工地安全初始化函数
 * ctx:输入参数,rknn_context句柄
 * path:输入参数,算法模型路径
 */
int site_safety_init(rknn_context *ctx, const char * path);


/* 
 * 工地安全执行函数
 * ctx:输入参数,rknn_context句柄
 * input_image:输入参数,图像数据输入(cv::Mat是Opencv的类型)
 * output_dets:输出参数，目标检测框输出
 */
int site_safety_run(rknn_context ctx, cv::Mat input_image, site_safety_result_group_t *detect_result_group);


/* 
 * 工地安全释放函数
 * ctx:输入参数,rknn_context句柄
 */
int site_safety_release(rknn_context ctx);




#endif
