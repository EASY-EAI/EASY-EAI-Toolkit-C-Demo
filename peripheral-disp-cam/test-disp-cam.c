#include <stdio.h>
#include <unistd.h>
#include <signal.h>

#include <disp.h>
#include <camera.h>
#include <rga/RgaApi.h>

#define CAMERA_WIDTH	720
#define CAMERA_HEIGHT	1280
#define	DISP_WIDTH		720
#define	DISP_HEIGHT		1280
#define	DISP_XOFF		0
#define	DISP_YOFF		0
#define	IMGRATIO		3
#define	IMAGE_SIZE		(CAMERA_WIDTH*CAMERA_HEIGHT*IMGRATIO)

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

	ret = rgbcamera_init(CAMERA_WIDTH, CAMERA_HEIGHT, 90);
	if (ret) {
		printf("error func:%s, line:%d\n", __func__, __LINE__);
		goto exit4;
	}

	ret = disp_init(DISP_WIDTH, DISP_HEIGHT); //RGB888 default
	if (ret) {
		printf("error func:%s, line:%d\n", __func__, __LINE__);
		goto exit3;
	}

	pbuf = (char *)malloc(IMAGE_SIZE);
	if (!pbuf) {
		printf("error: %s, %d\n", __func__, __LINE__);
		ret = -1;
		goto exit2;
	}

	g_run = 1;
	while(g_run) {
		ret = rgbcamera_getframe(pbuf);
		if (!ret) {
			//FILE *fp = fopen("/tmp/rgb", "w");
			//fwrite(pbuf, 1, IMAGE_SIZE, fp);
			//fclose(fp);
			disp_commit(pbuf, DISP_XOFF, DISP_YOFF);
		}
		else {
			printf("error: %s, %d\n", __func__, __LINE__);
			ret = -1;
			goto exit1;
		}
	}

exit1:
	free(pbuf);
	pbuf = NULL;
exit2:
	disp_exit();
exit3:
	rgbcamera_exit();
exit4:
    return ret;
}

