#ifndef _OCR_H_
#define _OCR_H_

#include "rknn_api.h"
//#include "common.h"
#include <string>
#include <opencv2/opencv.hpp>

#define MODEL_OUT_CHANNEL 6625

typedef struct {
    rknn_context rknn_ctx;
    rknn_input_output_num io_num;
    rknn_tensor_attr* input_attrs;
    rknn_tensor_attr* output_attrs;
    int model_channel;
    int model_width;
    int model_height;
} rknn_app_context_t;

typedef struct rknn_point_t
{
    int x;  ///< X Coordinate
    int y;  ///< Y Coordinate
} rknn_point_t;

typedef struct rknn_quad_t
{
    rknn_point_t left_top;      // Left top point
    rknn_point_t right_top;     // Right top point
    rknn_point_t left_bottom;   // Left bottom point
    rknn_point_t right_bottom;  // Right bottom point
    float score;
} rknn_quad_t;

typedef struct {
    rknn_quad_t box[1000];                             // text location bounding box，(left top/right top/right bottom/left bottom)
    int count;                                                             // box num
} ocr_det_result;


typedef struct ocr_det_postprocess_params {
    float threshold;
    float box_threshold;
    bool use_dilate;
    char* db_score_mode;
    char* db_box_type;
    float db_unclip_ratio;
} ocr_det_postprocess_params;

typedef struct ocr_rec_result
{
    char str[512];                                                    // text content
    int str_size;                                                          // text length
    float score;                                                           // text score
} ocr_rec_result;

int ocr_det_init(const char* model_path, rknn_app_context_t* app_ctx);

int ocr_det_release(rknn_app_context_t* app_ctx);

int ocr_det_run(rknn_app_context_t* app_ctx, cv::Mat input_image, ocr_det_postprocess_params* params, ocr_det_result* out_result);

int dbnet_postprocess(float* output, int det_out_w, int det_out_h, float db_threshold, float db_box_threshold, bool use_dilation,
                                                const std::string &db_score_mode, const float &db_unclip_ratio, const std::string &db_box_type,
                                                float scale_w, float scale_h, ocr_det_result* results);

cv::Mat GetRotateCropImage(const cv::Mat& srcimage, rknn_quad_t box_result);

int ocr_rec_init(const char* model_path, rknn_app_context_t* app_ctx);

int ocr_rec_release(rknn_app_context_t* app_ctx);

int ocr_rec_run(rknn_app_context_t* app_ctx, cv::Mat input_image, ocr_rec_result* out_result);

int rec_postprocess(float* out_data, int out_channel, int out_seq_len, ocr_rec_result* text);


#endif //_OCR_H_