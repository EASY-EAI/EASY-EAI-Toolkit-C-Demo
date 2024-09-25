#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

#include <disp.h>
#include <camera.h>

#define CAMERA_WIDTH	720
#define CAMERA_HEIGHT	1280
#define	DISP_WIDTH		720
#define	DISP_HEIGHT		1280
#define	IMGRATIO		3
#define	IMAGE_SIZE		(CAMERA_WIDTH*CAMERA_HEIGHT*IMGRATIO)

#define MIPICAMERA 

static int g_run = 0;
static void sigterm_handler(int sig) {
	fprintf(stderr, "signal %d\n", sig);
	g_run = 0;
}

int main()
{
	char *pbuf = NULL;
	int ret = 0;

	signal(SIGINT, sigterm_handler);

	/* camera init */
#ifdef MIPICAMERA
	ret = rgbcamera_init(CAMERA_WIDTH, CAMERA_HEIGHT, 270);
#else
	ret = usbcamera_init(USB2_0, USB_DIRECT, CAMERA_WIDTH, CAMERA_HEIGHT, 0);
#endif
	if (ret) {
		printf("error func:%s, line:%d\n", __func__, __LINE__);
		goto exit1;
	}

	/* display init */
	ret = disp_init(DISP_WIDTH, DISP_HEIGHT);
	if (ret) {
		printf("error func:%s, line:%d\n", __func__, __LINE__);
		goto exit2;
	}

	/* alloc buffer for cap data */
	pbuf = (char *)malloc(IMAGE_SIZE);
	if (!pbuf) {
		printf("error: %s, %d\n", __func__, __LINE__);
		ret = -1;
		goto exit3;
	}
	g_run = 1;
	while(g_run) {
		/* capture */
#ifdef MIPICAMERA
		ret = rgbcamera_getframe(pbuf);
#else
		ret = usbcamera_getframe(USB2_0, USB_DIRECT, pbuf);
#endif
		if (!ret) {
			/* display */
			disp_commit(pbuf, IMAGE_SIZE);
		}
	}

	free(pbuf);
	pbuf = NULL;
exit3:
	disp_exit();
exit2:
#ifdef MIPICAMERA
	rgbcamera_exit();
#else
	usbcamera_exit(USB2_0, USB_DIRECT);
#endif
exit1:
    return ret;
}

