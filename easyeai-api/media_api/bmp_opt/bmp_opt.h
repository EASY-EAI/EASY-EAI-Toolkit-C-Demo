 /**
 *
 * Copyright 2022 by Guangzhou Easy EAI Technologny Co.,Ltd.
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

#ifndef BMP_OPERATION_H
#define BMP_OPERATION_H

#include <stdint.h>

#if defined(__cplusplus)
extern "C" {
#endif

#pragma pack(1)
struct bmp_header { //这个结构体就是对上面那个图做一个封装。
    //bmp header
    uint8_t Signatue[2];	// B  M
    uint32_t FileSize;		//文件大小
    uint16_t Reserv1;
    uint16_t Reserv2;
    uint32_t FileOffset;	//文件头偏移量

    //DIB header
    uint32_t DIBHeaderSize;//DIB头大小
    uint32_t ImageWidth;	//文件宽度
    uint32_t ImageHight;	//文件高度
    uint16_t Planes;
    uint16_t BPP;			//每个相素点的位数
    uint32_t Compression;
    uint32_t ImageSize;	//图文件大小
    uint32_t XPPM;
    uint32_t YPPM;
    uint32_t CCT;
    uint32_t ICC;
};
#pragma pack()

extern uint32_t read_BMP_file(unsigned char *pOutputPIC, char *filename);
extern uint32_t save_BMP_file(char *filename, uint8_t *pBuff, uint16_t width, uint16_t height, int Bpp);

#if defined(__cplusplus)
}
#endif
#endif // BMP_OPERATION_H