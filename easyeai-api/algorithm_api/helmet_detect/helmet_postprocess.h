#ifndef HELMET_POSTPROCESS_H
#define HELMET_POSTPROCESS_H

#include <stdint.h>

#define HELMET_NAME_MAX_SIZE 16
#define HELMET_NUMB_MAX_SIZE 200
#define HELMET_CLASS_NUM     2
#define HELMET_PROP_BOX_SIZE     (5+HELMET_CLASS_NUM)

typedef struct
{
    int left;
    int right;
    int top;
    int bottom;
} HELMET_BOX_RECT;

typedef struct
{
    char name[HELMET_NAME_MAX_SIZE];
    int class_index;
    HELMET_BOX_RECT box;
    float prop;
} helmet_detect_result_t;

typedef struct
{
    int id;
    int count;
    helmet_detect_result_t results[HELMET_NUMB_MAX_SIZE];
} helmet_detect_result_group_t;

int helmet_post_process_u8(uint8_t *input0, uint8_t *input1, uint8_t *input2, int model_in_h, int model_in_w,
                 float conf_threshold, float nms_threshold,
                 std::vector<uint8_t> &qnt_zps, std::vector<float> &qnt_scales,
                 helmet_detect_result_group_t *group);

int helmet_post_process_fp(float *input0, float *input1, float *input2, int model_in_h, int model_in_w,
                 float conf_threshold, float nms_threshold, 
                 helmet_detect_result_group_t *group);

#endif //_RKNN_ZERO_COPY_DEMO_POSTPROCESS_H_
