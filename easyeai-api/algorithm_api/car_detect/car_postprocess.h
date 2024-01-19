#ifndef CAR_POSTPROCESS_H
#define CAR_POSTPROCESS_H

#include <stdint.h>

#define CAR_NAME_MAX_SIZE 16
#define CAR_NUMB_MAX_SIZE 200
#define CAR_CLASS_NUM     80
#define CAR_PROP_BOX_SIZE     (5+CAR_CLASS_NUM)

typedef struct
{
    int left;
    int right;
    int top;
    int bottom;
} CAR_BOX_RECT;

typedef struct
{
    char name[CAR_NAME_MAX_SIZE];
    int class_index;
    CAR_BOX_RECT box;
    float prop;
} car_detect_result_t;

typedef struct
{
    int id;
    int count;
    car_detect_result_t results[CAR_NUMB_MAX_SIZE];
} car_detect_result_group_t;

int car_post_process_u8(uint8_t *input0, uint8_t *input1, uint8_t *input2, int model_in_h, int model_in_w,
                 float conf_threshold, float nms_threshold,
                 std::vector<uint8_t> &qnt_zps, std::vector<float> &qnt_scales,
                 car_detect_result_group_t *group);

int car_post_process_fp(float *input0, float *input1, float *input2, int model_in_h, int model_in_w,
                 float conf_threshold, float nms_threshold, 
                 car_detect_result_group_t *group);

#endif //_RKNN_ZERO_COPY_DEMO_POSTPROCESS_H_
