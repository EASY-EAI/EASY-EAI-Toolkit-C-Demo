#ifndef PHONECALL_POSTPROCESS_H
#define PHONECALL_POSTPROCESS_H

#include <stdint.h>

#define PHONECALL_NAME_MAX_SIZE 16
#define PHONECALL_NUMB_MAX_SIZE 200
#define PHONECALL_CLASS_NUM     1
#define PHONECALL_PROP_BOX_SIZE     (5+PHONECALL_CLASS_NUM)

typedef struct
{
    int left;
    int right;
    int top;
    int bottom;
} PHONECALL_BOX_RECT;

typedef struct
{
    char name[PHONECALL_NAME_MAX_SIZE];
    int class_index;
    PHONECALL_BOX_RECT box;
    float prop;
} phonecall_detect_result_t;

typedef struct
{
    int id;
    int count;
    phonecall_detect_result_t results[PHONECALL_NUMB_MAX_SIZE];
} phonecall_detect_result_group_t;

int phonecall_post_process_u8(uint8_t *input0, uint8_t *input1, uint8_t *input2, int model_in_h, int model_in_w,
                 float conf_threshold, float nms_threshold,
                 std::vector<uint8_t> &qnt_zps, std::vector<float> &qnt_scales,
                 phonecall_detect_result_group_t *group);

int phonecall_post_process_fp(float *input0, float *input1, float *input2, int model_in_h, int model_in_w,
                 float conf_threshold, float nms_threshold, 
                 phonecall_detect_result_group_t *group);

#endif //_RKNN_ZERO_COPY_DEMO_POSTPROCESS_H_
