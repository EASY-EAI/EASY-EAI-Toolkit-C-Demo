#ifndef TOOLS_H
#define TOOLS_H
#include "face_detect.h"
#include <opencv2/opencv.hpp>


struct Transform_info
{
    int src_width;          //原图宽度
    int src_height;         //原图高度
    int target_width;       //目标宽度
    int target_height;      //目标高度
    int top;                //顶部补充像素数目
    int bottom;             //底部补充像素数目
    int left;               //左端补充像素数目
    int right;              //右端补充像素数目
    float ratio;            //缩放比例, src_width/target_width
};


void nms_cpu(std::vector<det>& boxes, 
             float threshold,
             std::vector<det> &filtered_output);
/*
描述：
    nms 极大值抑制

输入：
    boxes               待处理的det数据组
    threashold          阈值，面积大于阈值的，则可能被抑制
    filtered_output     输出的det数据组

输出：
    无

*/

void letter_box(cv::Mat &src, 
                cv::Mat &dst, 
                int width, 
                int height, 
                struct Transform_info *t_info);
/*
描述：
    opencv补边，不改变原图尺寸比例的情况下，缩放到想要的大小

输入：
    src                 原图
    dst                 返回图
    width               目标宽度
    height              目标高度
    t_info              记录变换结构结果

输出：
    无
    
*/

#endif