/**
 *
 * Copyright 2021 by Guangzhou Easy EAI Technologny Co.,Ltd.
 * website: www.easy-eai.com
 *
 * Author: JX <liaojunxian@easy-eai.com>
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * License file for more details.
 * 
 */

#ifndef QRDECODE_H
#define QRDECODE_H

#include <stdio.h>
#include <stdint.h>


#if defined(__cplusplus)
extern "C" {
#endif

struct qrcode_info {
    int x1;
    int x2;
    int y1;
    int y2;
    char result[200];
    char type[20];
};

/* 
 * 二维码检测运行函数
 * src:输入参数, Opencv Mat格式图像
 * p_info：输出参数, 二维码检测的结果输出
 */
int qr_decode(cv::Mat src, struct qrcode_info *p_info);


#if defined(__cplusplus)
}
#endif

#endif // QRDECODE_H
