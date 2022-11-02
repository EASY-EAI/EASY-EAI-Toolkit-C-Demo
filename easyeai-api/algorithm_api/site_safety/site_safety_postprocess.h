#ifndef SITE_SAFETY_POSTPROCESS_H
#define SITE_SAFETY_POSTPROCESS_H

#include <stdint.h>

#define SITE_SAFETY_NAME_MAX_SIZE 16
#define SITE_SAFETY_NUMB_MAX_SIZE 200
#define SITE_SAFETY_CLASS_NUM     3
#define SITE_SAFETY_PROP_BOX_SIZE     (5+ SITE_SAFETY_CLASS_NUM)

typedef struct _SITE_SAFETY_BOX_RECT
{
    int left;
    int right;
    int top;
    int bottom;
} SITE_SAFETY_BOX_RECT;

typedef struct __site_safety_result_t
{
    char name[SITE_SAFETY_NUMB_MAX_SIZE];
    int class_index;
    SITE_SAFETY_BOX_RECT box;
    float prop;
} site_safety_result_t;

typedef struct _site_safety_detect_result_group_t
{
    int id;
    int count;
    site_safety_result_t results[SITE_SAFETY_NUMB_MAX_SIZE];
} site_safety_result_group_t;

int site_safety_post_process_u8(uint8_t *input0, uint8_t *input1, uint8_t *input2, int model_in_h, int model_in_w,
                 float conf_threshold, float nms_threshold,
                 std::vector<uint8_t> &qnt_zps, std::vector<float> &qnt_scales,
                 site_safety_result_group_t *group);

int site_safety_post_process_fp(float *input0, float *input1, float *input2, int model_in_h, int model_in_w,
                 float conf_threshold, float nms_threshold, 
                 site_safety_result_group_t *group);

#endif 
