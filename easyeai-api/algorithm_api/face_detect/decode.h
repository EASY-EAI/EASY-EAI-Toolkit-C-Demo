#ifndef DECODE_H
#define DEOCDE_H

#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <stdlib.h>
#include "face_detect.h"

void decode_box_and_landmark(float* confident, 
                             float* loc, 
                             float* predict, 
                             float score_threshold, 
                             float nms_threshold,
                             std::vector<std::vector<float>> &prior_data,
                             std::vector<det> &outputs);
/*
描述：
    解码人脸框和人脸关键点

*/


#endif