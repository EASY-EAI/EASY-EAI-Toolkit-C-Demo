#ifndef FACE_RECOGNITION_H
#define FACE_RECOGNITION_H

#include "rknn_api.h"


/* 
 * 人脸识别初始化函数
 * ctx:输入参数,rknn_context句柄
 * path:输入参数,算法模型路径
 */
int face_recognition_init(rknn_context *ctx, const char * path);

/* 
 * 人脸识别执行函数
 * ctx:输入参数,rknn_context句柄
 * face_image:输入参数,图像数据输入(cv::Mat是Opencv的类型)
 * feature:输出参数，算法输出的人脸特征码
 */
int face_recognition_run(rknn_context ctx, cv::Mat *face_image, float (*feature)[512]);

/* 
 * 人脸识别特征比对函数
 * feature_1:输入参数,人脸特征码1
 * feature_2:输入参数,人脸特征码2
 */
float face_recognition_comparison(float *feature_1, float *feature_2, int output_len);

/* 
 * 人脸识别释放函数
 * ctx:输入参数,rknn_context句柄
 */
int face_recognition_release(rknn_context ctx);

#endif
