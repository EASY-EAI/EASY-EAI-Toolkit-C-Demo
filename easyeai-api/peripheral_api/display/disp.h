/**
 *
 * Copyright 2021 by Guangzhou Easy EAI Technologny Co.,Ltd.
 * website: www.easy-eai.com
 *
 * Author: CHM <chenhaiman@easy-eai.com>
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * License file for more details.
 * 
 */

#ifndef DISP_H
#define DISP_H

#ifdef __cplusplus
extern "C" {
#endif

#include <rga/RgaApi.h>

/* 默认输入RGB888，可通过disp_set_format修改*/
void disp_preset_uiLayer(int enable);
int disp_init(int width, int height);
void disp_exit(void);
void disp_commit(void *ptr, int x_off, int y_off);
void disp_set_format(RgaSURF_FORMAT fmt);


#ifdef __cplusplus
}
#endif
#endif

