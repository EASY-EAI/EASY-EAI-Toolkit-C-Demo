#ifndef SELF_LEARNING_H
#define SELF_LEARNING_H

#include "rknn_api.h"
#include <opencv2/opencv.hpp>

struct self_learning_data
{
	int class_num;
	float feature[512];
};

/* 
 * 自学习初始化函数
 * ctx:输入参数,rknn_context句柄
 * path:输入参数,算法模型路径
 */
int self_learning_init(rknn_context *ctx, const char *path);

/* 
 * 自学习训练函数
 * ctx:输入参数,rknn_context句柄
 * input_image：输入参数,图像数据输入(cv::Mat是Opencv的类型)
 * p_train_data:输入参数,struct self_learning_data类型的用于训练的数组
 * class_num:输入参数，物体的类别
 */
int self_learning_train(rknn_context ctx, cv::Mat input_image, struct self_learning_data *p_train_data, int class_num);

/* 
 * 自学习推断函数
 * ctx:输入参数,rknn_context句柄
 * input_image：输入参数,图像数据输入(cv::Mat是Opencv的类型)
 * p_train_data:输入参数,struct self_learning_data类型的用于训练的数组
 * train_data_sum：输入参数，训练样本总数
 * class_num:输入参数，物体的类别
 * k_value:输入参数， 算法k值(要输入3、5、8...等单数)，训练数据量越大,k值可以适当增大,算法稳定性也会增强
 */
int self_learning_inference(rknn_context ctx, cv::Mat input_image, struct self_learning_data *p_train_data, int train_data_sum, int k_value);

/* 
 * 自学习释放函数
 * ctx:输入参数,rknn_context句柄
 */
int self_learning_release(rknn_context ctx);

#endif
