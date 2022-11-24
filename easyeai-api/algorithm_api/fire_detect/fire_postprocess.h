#ifndef FIRE_POSTPROCESS_H
#define FIRE_POSTPROCESS_H

#include <stdint.h>

#define FIRE_NAME_MAX_SIZE 16
#define FIRE_NUMB_MAX_SIZE 200
#define FIRE_CLASS_NUM     1
#define FIRE_PROP_BOX_SIZE     (5+FIRE_CLASS_NUM)

typedef struct
{
    int left;
    int right;
    int top;
    int bottom;
} FIRE_BOX_RECT;

typedef struct
{
    char name[FIRE_NAME_MAX_SIZE];
    int class_index;
    FIRE_BOX_RECT box;
    float prop;
} fire_detect_result_t;

typedef struct
{
    int id;
    int count;
    fire_detect_result_t results[FIRE_NUMB_MAX_SIZE];
} fire_detect_result_group_t;

int fire_post_process_u8(uint8_t *input0, uint8_t *input1, uint8_t *input2, int model_in_h, int model_in_w,
                 float conf_threshold, float nms_threshold,
                 std::vector<uint8_t> &qnt_zps, std::vector<float> &qnt_scales,
                 fire_detect_result_group_t *group);

int fire_post_process_fp(float *input0, float *input1, float *input2, int model_in_h, int model_in_w,
                 float conf_threshold, float nms_threshold, 
                 fire_detect_result_group_t *group);

#endif //_RKNN_ZERO_COPY_DEMO_POSTPROCESS_H_
