 /**
 *
 * Copyright 2021 by Guangzhou Easy EAI Technologny Co.,Ltd.
 * website: www.easy-eai.com
 *
 * Author: Jiehao.Zhong <zhongjiehao@easy-eai.com>
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * License file for more details.
 * 
 */

#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <pthread.h>


#if defined(__cplusplus)
extern "C" {
#endif

typedef struct{
    float x;
    float y;
}fPoint_t;
typedef struct{
    float left;   //x1
    float top;    //y1
    float right;  //x2
    float bottom; //y2
}fRect_t;

typedef struct{
    int32_t x;
    int32_t y;
}s32Point_t;
typedef struct{
    int32_t left;   //x1
    int32_t top;    //y1
    int32_t right;  //x2
    int32_t bottom; //y2
}s32Rect_t;

/* 功能：判断点是否在矩形内
 * 
 */
extern bool point_in_rect(s32Point_t point, s32Rect_t rect);

/* 功能：计算矩形面积
 * 
 */
extern int32_t calc_rect_square(s32Rect_t rect);

/* 功能：找出面积较小矩形
 * 
 */
extern s32Rect_t min_rect(s32Rect_t rect1, s32Rect_t rect2);

/* 功能：找出面积较大矩形
 * 
 */
extern s32Rect_t max_rect(s32Rect_t rect1, s32Rect_t rect2);

/* 功能：判断矩形是否相交或相切
 * 
 */
extern bool rect_is_intersect(s32Rect_t rect1, s32Rect_t rect2);

/* 功能：计算两矩形相交部分面积(若相切，面积也为0)
 * 
 */
extern int32_t calc_rect_intersect_square(s32Rect_t rect1, s32Rect_t rect2);

/* 功能：计算[两矩形相交部分面积]与[小矩形面积]之比
 * 
 */
extern double calc_intersect_of_min_rect(s32Rect_t rect1, s32Rect_t rect2);

/* 功能：计算两矩形的交并比
 * 
 */
extern double calc_intersect_of_union(s32Rect_t rect1, s32Rect_t rect2);

#if defined(__cplusplus)
}
#endif
#endif // GEOMETRY_H