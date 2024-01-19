//
// Created by cai on 2021/10/14.
//

#ifndef OCR_DETECT_H
#define OCR_DETECT_H

#include "rknn_api.h"

#include "opencv2/opencv.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "clipper.h"
#include "OcrUtils.h"


class OCRDetection {
public:
    ~OCRDetection();

    int initModel(const char *filename);
    std::vector<ImgBox> getTextImages(cv::Mat &src);
    void clear();                      // 销毁引擎

private:
    rknn_context ctx{};
    rknn_input_output_num io_num{};
    int input_width{} ;
    int input_height{};

    const float boxScoreThresh = 0.6f;
    const float boxThresh = 0.3f;
    const float unClipRatio = 2.0f;
};

#endif //OCR_DETECT_H
