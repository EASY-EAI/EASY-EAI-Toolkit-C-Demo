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

#ifndef __CAMERA_H__
#define __CAMERA_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <rga/RgaApi.h>

#define	USB_OTG		1
#define	USB2_0		3
#define	USB_DIRECT	0
/* usb camera */
int usbcamera_init(int bus, int port, int width, int height, int rot);
void usbcamera_exit(int bus, int port);
int usbcamera_getframe(int bus, int port, char *pbuf);

/* rgb camera */
int rgbcamera_init(int width, int height, int rot);
void rgbcamera_exit(void);
int rgbcamera_getframe(char *pbuf);

/* ir camera */
int ircamera_init(int width, int height, int rot);
void ircamera_exit(void);
int ircamera_getframe(char *pbuf);

#ifdef __cplusplus
}
#endif
#endif
