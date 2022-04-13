#ifndef FACE_DETECT_H
#define FACE_DETECT_H

#include<opencv2/opencv.hpp>
#include <stdio.h>
#include <stdlib.h>
#include "rknn_api.h"



class det {
public:
    det(){
		landmarks.resize(5);
    }
    ~det(){
    }

    bool operator<(const det &t) const {
		return score < t.score;
	}

    bool operator>(const det &t) const {
		return score > t.score;
	}

    cv::Rect_<float> box;
    std::vector<cv::Point2f> landmarks;
    float score;

    void print() {
		printf("finalbox(x1y1x2y2) %f %f %f %f, score %f\n", box.x, box.y, box.br().x, box.br().y, score);
		printf("landmarks ");
		int point_number = landmarks.size();
		for (int i = 0; i < point_number; i++) {
			printf("%f %f, ", landmarks[i].x, landmarks[i].y);
		}
		printf("\n");
	}
    
};

/* 
 * 人脸检测初始化函数
 * ctx:输入参数,rknn_context句柄
 * path:输入参数,算法模型路径
 */
int face_detect_init(rknn_context *ctx, const char *path);

/* 
 * 人脸检测运行函数
 * ctx:输入参数, rknn_context句柄
 * input_image:输入参数, Opencv Mat格式图像
 * result：输出参数, 人脸检测的结果输出
 */
int face_detect_run(rknn_context ctx, cv::Mat &input_image, std::vector<det> &result);

/* 
 * 人脸释放函数
 * ctx:输入参数, rknn_context句柄
 */
int face_detect_release(rknn_context ctx);


#endif
