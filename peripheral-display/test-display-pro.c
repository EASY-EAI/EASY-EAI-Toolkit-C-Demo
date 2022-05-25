#include <stdio.h>
#include <unistd.h>
#include <signal.h>

#include <disp.h>
#include <rga/RgaApi.h>

#define	DISP_WIDTH		720
#define	DISP_HEIGHT		1280
#define	IMAGE_PATH		"720X1280.rgb"
#define	IMGRATIO		3.0f
#define	IMAGE_SIZE		(1280*720*IMGRATIO)

static int g_run = 0;
static void sigterm_handler(int sig) {
	fprintf(stderr, "signal %d\n", sig);
	g_run = 0;
}

int main()
{
	char *pbuf = NULL;
	int ret = 0;
	FILE *fp = NULL;
	disp_screen_t screen = {0};

	signal(SIGINT, sigterm_handler);

	/* 1、准备图像数据 */
	pbuf = (char *)malloc(IMAGE_SIZE);
	if (!pbuf) {
		printf("malloc error: %s, %d\n", __func__, __LINE__);
		return -1;
	}
	fp = fopen(IMAGE_PATH, "r");
	if (!fp) {
		printf("fopen error: %s, %d\n", __func__, __LINE__);
		free(pbuf);
		return -1;
	}
	ret = fread(pbuf, 1, IMAGE_SIZE, fp);
	fclose(fp);
	if (ret != IMAGE_SIZE) {
		printf("fread error: %s, %d\n", __func__, __LINE__);
		free(pbuf);
		return -1;
	}

	/* 2、初始化显示 */
	screen.screen_width = DISP_WIDTH;
	screen.screen_height = DISP_HEIGHT;
	screen.wins[0].enable = 1;
	screen.wins[0].in_fmt = IMAGE_TYPE_RGB888;
	screen.wins[0].in_w = DISP_WIDTH;
	screen.wins[0].in_h = DISP_HEIGHT;
	screen.wins[0].HorStride = DISP_WIDTH;
	screen.wins[0].VirStride = DISP_HEIGHT;
	screen.wins[0].crop_x = 0;
	screen.wins[0].crop_y = 0;
	screen.wins[0].crop_w = 720;
	screen.wins[0].crop_h = 720;
	screen.wins[0].rotation = 0;
	screen.wins[0].win_x = 0;
	screen.wins[0].win_y = 0;
	screen.wins[0].win_w = 360;
	screen.wins[0].win_h = 360;

	screen.wins[1].enable = 1;
	screen.wins[1].in_fmt = IMAGE_TYPE_RGB888;
	screen.wins[1].in_w = DISP_WIDTH;
	screen.wins[1].in_h = DISP_HEIGHT;
	screen.wins[1].HorStride = DISP_WIDTH;
	screen.wins[1].VirStride = DISP_HEIGHT;
	screen.wins[1].crop_x = 0;
	screen.wins[1].crop_y = 0;
	screen.wins[1].crop_w = DISP_WIDTH;
	screen.wins[1].crop_h = DISP_HEIGHT;
	screen.wins[1].rotation = 0;
	screen.wins[1].win_x = 300;
	screen.wins[1].win_y = 600;
	screen.wins[1].win_w = 360;
	screen.wins[1].win_h = 640;

	ret = disp_init_pro(&screen);
	if (ret) {
		printf("error func:%s, line:%d\n", __func__, __LINE__);
		goto exit1;
	}

	/* 3、提交显示 */
	disp_commit_pro(pbuf, 0, IMAGE_SIZE);
	sleep(1);
	disp_commit_pro(pbuf, 1, IMAGE_SIZE);

	g_run++;
	while(g_run) {
		sleep(1);
	}

	disp_exit_pro();
exit1:
	free(pbuf);
	pbuf = NULL;

    return ret;
}

