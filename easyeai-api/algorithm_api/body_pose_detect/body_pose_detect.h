#ifndef BODY_POSE_DETECT_H
#define BODY_POSE_DETECT_H

#include "body_pose_detect_postprocess.h"
#include "rknn_api.h"
#include <opencv2/opencv.hpp>


/* 
 * 姿态估计初始化函数
 * ctx:输入参数,rknn_context句柄
 * path:输入参数,算法模型路径
 */
int body_pose_detect_init(rknn_context *ctx, const char * path);


/* 
 * 姿态估计执行函数
 * ctx:输入参数,rknn_context句柄
 * input_image:输入参数,图像数据输入(cv::Mat是Opencv的类型)
 * output_dets:输出参数，目标检测框输出
 * keyPointsList:按组存放检测出的各个部位关节点信息
 * detectedKeypoints:依照keyPointsList的顺序将骨骼点存入的数组
 * personwiseKeypoints:按照detectedKeypoints的顺序给骨骼点进行匹配
 */
int body_pose_detect_run(rknn_context ctx, cv::Mat input_image, std::vector<KeyPoint_body>& keyPointsList, std::vector<std::vector<KeyPoint_body>>& detectedKeypoints, std::vector<std::vector<int>>& personwiseKeypoints);


/* 
 * 姿态估计释放函数
 * ctx:输入参数,rknn_context句柄
 */
int body_pose_detect_release(rknn_context ctx);


#endif
