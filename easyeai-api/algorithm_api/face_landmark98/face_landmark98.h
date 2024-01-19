#ifndef _FACE_LANDMARK98_H_
#define _FACE_LANDMARK98_H_

#include "rknn_api.h"
#include <opencv2/opencv.hpp>

/* Declarative Area */
typedef struct KeyPoint{
    int id;
    cv::Point point;
    float probability;
} KeyPointType;

/* 
 * 人脸98个关键点定位初始化函数
 * ctx:输入参数,rknn_context句柄
 * path:输入参数,算法模型路径
 */
int face_landmark98_init(rknn_context *ctx, const char * path);

/* 
 * 人脸98个关键点定位执行函数
 * ctx:输入参数,rknn_context句柄
 * face_image:输入参数,图像数据输入(cv::Mat是Opencv的类型)
 * keyPoints:输出参数，算法输出的人脸关键点坐标
 */
int face_landmark98_run(rknn_context ctx, cv::Mat *face_image, std::vector<KeyPointType> *keyPoints);

/* 
 * 人脸98个关键点定位释放函数
 * ctx:输入参数,rknn_context句柄
 */
int face_landmark98_release(rknn_context ctx);

/* 
 * keyPoints 输入参数，算法输出的人脸关键点坐标
 * 参考值：0.00235, 大于该值则为 睁眼， 反之闭眼
 */

float calculate_left_eye_area(std::vector<KeyPointType>* keyPoints);

/* 
 * keyPoints 输入参数，算法输出的人脸关键点坐标
 * 参考值：0.00235, 大于该值则为 睁眼， 反之闭眼
 */
float calculate_right_eye_area(std::vector<KeyPointType>* keyPoints);

/* 
 * keyPoints 输入参数，算法输出的人脸关键点坐标
 * 参考值：0.028, 大于该值则为 睁眼， 反之闭眼
 */
float calculate_mouth_area(std::vector<KeyPointType>* keyPoints);


#endif
