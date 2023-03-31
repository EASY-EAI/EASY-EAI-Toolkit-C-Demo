#ifndef SMOKE_POSTPROCESS_H
#define SMOKE_POSTPROCESS_H

#include <stdint.h>

#define SMOKE_NAME_MAX_SIZE 16
#define SMOKE_NUMB_MAX_SIZE 200
#define SMOKE_CLASS_NUM     1
#define SMOKE_PROP_BOX_SIZE     (5+SMOKE_CLASS_NUM)

typedef struct
{
    int left;
    int right;
    int top;
    int bottom;
} SMOKE_BOX_RECT;

typedef struct
{
    char name[SMOKE_NAME_MAX_SIZE];
    int class_index;
    SMOKE_BOX_RECT box;
    float prop;
} smoke_detect_result_t;

typedef struct
{
    int id;
    int count;
    smoke_detect_result_t results[SMOKE_NUMB_MAX_SIZE];
} smoke_detect_result_group_t;

int smoke_post_process_u8(uint8_t *input0, uint8_t *input1, uint8_t *input2, int model_in_h, int model_in_w,
                 float conf_threshold, float nms_threshold,
                 std::vector<uint8_t> &qnt_zps, std::vector<float> &qnt_scales,
                 smoke_detect_result_group_t *group);

int smoke_post_process_fp(float *input0, float *input1, float *input2, int model_in_h, int model_in_w,
                 float conf_threshold, float nms_threshold, 
                 smoke_detect_result_group_t *group);

#endif //_RKNN_ZERO_COPY_DEMO_POSTPROCESS_H_
