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

static int g_run = 0;
static void sigterm_handler(int sig) {
	fprintf(stderr, "signal %d\n", sig);
	g_run = 0;
}

int main()
{
	char *prgb = NULL;
	char *pir = NULL;
	int ret = 0;
	disp_screen_t screen = {0};

	signal(SIGINT, sigterm_handler);

	/* camera init */
	ret = rgbcamera_init(CAMERA_WIDTH, CAMERA_HEIGHT, 270);
	if (ret) {
		printf("error func:%s, line:%d\n", __func__, __LINE__);
		goto exit1;
	}
	ret = ircamera_init(CAMERA_WIDTH, CAMERA_HEIGHT, 270); //此角度由摄像头模组决定
	if (ret) {
		printf("error func:%s, line:%d\n", __func__, __LINE__);
		goto exit2;
	}

	/* display init */
	screen.screen_width = DISP_WIDTH;
	screen.screen_height = DISP_HEIGHT;
	screen.wins[0].enable = 1;
	screen.wins[0].in_fmt = IMAGE_TYPE_BGR888;
	screen.wins[0].in_w = CAMERA_WIDTH;
	screen.wins[0].in_h = CAMERA_HEIGHT;
	screen.wins[0].rotation = 0;
	screen.wins[0].win_x = 0;
	screen.wins[0].win_y = 0;
	screen.wins[0].win_w = 360;
	screen.wins[0].win_h = 640;
	screen.wins[1].enable = 1;
	screen.wins[1].in_fmt = IMAGE_TYPE_BGR888;
	screen.wins[1].in_w = CAMERA_WIDTH;
	screen.wins[1].in_h = CAMERA_HEIGHT;
	screen.wins[1].rotation = 0;
	screen.wins[1].win_x = 300;
	screen.wins[1].win_y = 600;
	screen.wins[1].win_w = 360;
	screen.wins[1].win_h = 640;
	ret = disp_init_pro(&screen);
	if (ret) {
		printf("error func:%s, line:%d\n", __func__, __LINE__);
		goto exit3;
	}

	/* alloc buffer for cap data */
	prgb = (char *)malloc(IMAGE_SIZE);
	if (!prgb) {
		printf("error: %s, %d\n", __func__, __LINE__);
		ret = -1;
		goto exit4;
	}
	pir = (char *)malloc(IMAGE_SIZE);
	if (!pir) {
		printf("error: %s, %d\n", __func__, __LINE__);
		ret = -1;
		goto exit5;
	}

	g_run = 1;
	while(g_run) {
		ret = rgbcamera_getframe(prgb);
		if (!ret) {
			disp_commit_pro(prgb, 0, IMAGE_SIZE);
		}
		ret = ircamera_getframe(pir);
		if (!ret) {
			disp_commit_pro(pir, 1, IMAGE_SIZE);
		}
	}

	free(pir);
	pir = NULL;
exit5:
	free(prgb);
	prgb = NULL;
exit4:
	disp_exit_pro();
exit3:
	ircamera_exit();
exit2:
	rgbcamera_exit();
exit1:
    return ret;
}


