#ifndef GENERATOR_H
#define GENERATOR_H

#include <string.h>
#include <vector>
#include <iostream>
#include <cmath>
#include<opencv2/opencv.hpp>
#include "generator.h"


using namespace std;


vector<vector<float>> generate_prior_data(int width, int height);
/*
简述：
    生成prior_data。
参数：
    width           图片宽度
    height          图片高度
返回：
    二维浮点数vector，D1是数目，D2是单个先验数据长度。
*/


void decode_box(float *loc, 
                const vector<float> &single_prior_data, 
                cv::Rect_<float> &rect);
/*
简述：
    根据prior_data、预测值，解码出单个人脸框信息
参数：
    loc                 一组模型的loc预测值
    single_prior_data   单个prior_data(先验数据)
    box                 box数组，结果返回在其中
返回：
    无
*/



void decode_landmark(float *predict, 
                     const vector<float> &single_prior_data, 
                     vector<cv::Point2f> &landmark);
/*
简述：
    根据prior_data、预测值，解码出单个人脸关键点信息。
参数：
    predict             一组模型的predict预测值
    single_prior_data   单个prior_data(先验数据)
    landmark            landmark数组，结果返回在其中
返回：
    无
*/

#endif




