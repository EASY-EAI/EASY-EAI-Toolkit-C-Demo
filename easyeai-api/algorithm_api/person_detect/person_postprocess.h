#ifndef PERSON_POSTPROCESS_H
#define PERSON_POSTPROCESS_H

#include <stdint.h>

#define PERSON_NAME_MAX_SIZE 16
#define PERSON_NUMB_MAX_SIZE 200
#define PERSON_CLASS_NUM     1
#define PERSON_PROP_BOX_SIZE     (5+PERSON_CLASS_NUM)

typedef struct
{
    int left;
    int right;
    int top;
    int bottom;
} PERSON_BOX_RECT;

typedef struct
{
    char name[PERSON_NAME_MAX_SIZE];
    int class_index;
    PERSON_BOX_RECT box;
    float prop;
} person_detect_result_t;

typedef struct
{
    int id;
    int count;
    person_detect_result_t results[PERSON_NUMB_MAX_SIZE];
} person_detect_result_group_t;

int person_post_process_u8(uint8_t *input0, uint8_t *input1, uint8_t *input2, int model_in_h, int model_in_w,
                 float conf_threshold, float nms_threshold,
                 std::vector<uint8_t> &qnt_zps, std::vector<float> &qnt_scales,
                 person_detect_result_group_t *group);

int person_post_process_fp(float *input0, float *input1, float *input2, int model_in_h, int model_in_w,
                 float conf_threshold, float nms_threshold, 
                 person_detect_result_group_t *group);

#endif //_RKNN_ZERO_COPY_DEMO_POSTPROCESS_H_
