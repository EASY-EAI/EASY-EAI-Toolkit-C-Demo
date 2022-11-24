#ifndef _FACE_MASK_JUDGEMENT_H_
#define _FACE_MASK_JUDGEMENT_H_

#include "rknn_api.h"


/* 
 * 人脸口罩判断初始化
 * ctx:输入参数,rknn_context句柄
 * path:输入参数,算法模型路径
 */
int face_mask_judgement_init(rknn_context *ctx, const char * path);

/* 
 * 人脸口罩判断执行函数
 * ctx:输入参数,rknn_context句柄
 * face_image:输入参数,图像数据输入(cv::Mat是Opencv的类型)
 * result:输出参数，算法输出的二分类概率结果
 */
int face_mask_judgement_run(rknn_context ctx, cv::Mat *face_image, float *result);

/* 
 * 人脸口罩判断释放函数
 * ctx:输入参数,rknn_context句柄
 */
int face_mask_judgement_release(rknn_context ctx);

#endif
