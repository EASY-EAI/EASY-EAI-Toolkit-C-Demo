#ifndef _FACE_ALIGNMENT_H_
#define _FACE_ALIGNMENT_H_

#include "rknn_api.h"
#include<opencv2/opencv.hpp>

cv::Mat face_alignment(cv::Mat img, cv::Point2f* points);

#endif
