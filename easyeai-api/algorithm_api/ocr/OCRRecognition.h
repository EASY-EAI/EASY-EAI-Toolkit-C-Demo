//
// Created by cai on 2021/9/10.
//

#ifndef OCR_RECOGNITION_H
#define OCR_RECOGNITION_H

#include "rknn_api.h"
#include "opencv2/opencv.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "OcrUtils.h"

using namespace std;
using namespace cv;

class OCRRecognition{
public:
    ~OCRRecognition();

    int initModel(const char*filename,const char *keys_path);           // 加载初始化模型

    std::vector<StringBox> inference(std::vector<ImgBox> crop_img);           // 模型推理

    void clear();                      // 销毁引擎

private:
    std::vector<std::string> keys;
    rknn_context ctx;
    rknn_input_output_num io_num;
    int input_width ;
    int input_height;

};

#endif //RKNN_MOBILENET_DEMO_LINUX_OCRRecognition_RKNN_H
