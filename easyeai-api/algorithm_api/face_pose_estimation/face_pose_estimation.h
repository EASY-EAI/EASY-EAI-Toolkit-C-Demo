#ifndef _FACE_POSE_ESTIMATION_H_
#define _FACE_POSE_ESTIMATION_H_

#include "rknn_api.h"


/* 
 * 人脸姿态初始化函数
 * ctx:输入参数,rknn_context句柄
 * path:输入参数,算法模型路径
 */
int face_pose_estimation_init(rknn_context *ctx, const char * path);

/* 
 * 人脸姿态执行函数
 * ctx:输入参数,rknn_context句柄
 * face_image:输入参数,图像数据输入(cv::Mat是Opencv的类型)
 * result:输出参数，yaw(偏航角), pitch(俯仰角), roll(翻滚角)
 */
int face_pose_estimation_run(rknn_context ctx, cv::Mat *face_image, float *result);

/* 
 * 人脸姿态释放函数
 * ctx:输入参数,rknn_context句柄
 */
int face_pose_estimation_release(rknn_context ctx);

#endif
