#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include <stdlib.h>

#include <disp.h>

#define	DISP_WIDTH		720
#define	DISP_HEIGHT		1280
#define	IMAGE_PATH		"720X1280.rgb"
#define	IMGRATIO		3.0f
#define	IMAGE_SIZE		(1280*720*IMGRATIO)

typedef struct {
	pthread_t th;
	char *pbuf;
	int win_num;
} my_win_t;

static int g_run = 0;

static void sigterm_handler(int sig) {
	fprintf(stderr, "signal %d\n", sig);
	g_run = 0;
}

static void *disp_thread(void *arg)
{
	my_win_t *win = NULL;

	win = (my_win_t *)arg;
	while(g_run){
		disp_commit_pro(win->pbuf, win->win_num, IMAGE_SIZE);
		//printf("th:%lu, win_num:%d.\n", win->th, win->win_num);
	}
	return NULL;
}

int main()
{
	int ret = 0;
	FILE *fp = NULL;
	disp_screen_t screen = {0};
	my_win_t my_wins[6] = {0};

	signal(SIGINT, sigterm_handler);

	/* 1、准备图像数据 */
	for(int i = 0; i < 6; i++){
		my_wins[i].pbuf = (char *)malloc(IMAGE_SIZE);
		if (!my_wins[i].pbuf) {
			printf("malloc error: %s, %d\n", __func__, __LINE__);
			return -1;
		}
	}
	fp = fopen(IMAGE_PATH, "r");
	if (!fp) {
		printf("fopen error: %s, %d\n", __func__, __LINE__);
		return -1;
	}
	for(int i = 0; i < 6; i++){
		fseek(fp, 0, SEEK_SET);
		fread(my_wins[i].pbuf, 1, IMAGE_SIZE, fp);
	}

	fclose(fp);

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
	screen.wins[1].crop_w = 720;
	screen.wins[1].crop_h = 720;
	screen.wins[1].rotation = 0;
	screen.wins[1].win_x = 360;
	screen.wins[1].win_y = 0;
	screen.wins[1].win_w = 360;
	screen.wins[1].win_h = 360;

	screen.wins[2].enable = 1;
	screen.wins[2].in_fmt = IMAGE_TYPE_RGB888;
	screen.wins[2].in_w = DISP_WIDTH;
	screen.wins[2].in_h = DISP_HEIGHT;
	screen.wins[2].HorStride = DISP_WIDTH;
	screen.wins[2].VirStride = DISP_HEIGHT;
	screen.wins[2].crop_x = 0;
	screen.wins[2].crop_y = 0;
	screen.wins[2].crop_w = 720;
	screen.wins[2].crop_h = 720;
	screen.wins[2].rotation = 0;
	screen.wins[2].win_x = 0;
	screen.wins[2].win_y = 360;
	screen.wins[2].win_w = 360;
	screen.wins[2].win_h = 360;

	screen.wins[3].enable = 1;
	screen.wins[3].in_fmt = IMAGE_TYPE_RGB888;
	screen.wins[3].in_w = DISP_WIDTH;
	screen.wins[3].in_h = DISP_HEIGHT;
	screen.wins[3].HorStride = DISP_WIDTH;
	screen.wins[3].VirStride = DISP_HEIGHT;
	screen.wins[3].crop_x = 0;
	screen.wins[3].crop_y = 0;
	screen.wins[3].crop_w = 720;
	screen.wins[3].crop_h = 720;
	screen.wins[3].rotation = 0;
	screen.wins[3].win_x = 360;
	screen.wins[3].win_y = 360;
	screen.wins[3].win_w = 360;
	screen.wins[3].win_h = 360;

	screen.wins[4].enable = 1;
	screen.wins[4].in_fmt = IMAGE_TYPE_RGB888;
	screen.wins[4].in_w = DISP_WIDTH;
	screen.wins[4].in_h = DISP_HEIGHT;
	screen.wins[4].HorStride = DISP_WIDTH;
	screen.wins[4].VirStride = DISP_HEIGHT;
	screen.wins[4].crop_x = 0;
	screen.wins[4].crop_y = 0;
	screen.wins[4].crop_w = 720;
	screen.wins[4].crop_h = 720;
	screen.wins[4].rotation = 0;
	screen.wins[4].win_x = 0;
	screen.wins[4].win_y = 720;
	screen.wins[4].win_w = 360;
	screen.wins[4].win_h = 360;

	screen.wins[5].enable = 1;
	screen.wins[5].in_fmt = IMAGE_TYPE_RGB888;
	screen.wins[5].in_w = DISP_WIDTH;
	screen.wins[5].in_h = DISP_HEIGHT;
	screen.wins[5].HorStride = DISP_WIDTH;
	screen.wins[5].VirStride = DISP_HEIGHT;
	screen.wins[5].crop_x = 0;
	screen.wins[5].crop_y = 0;
	screen.wins[5].crop_w = 720;
	screen.wins[5].crop_h = 720;
	screen.wins[5].rotation = 0;
	screen.wins[5].win_x = 360;
	screen.wins[5].win_y = 720;
	screen.wins[5].win_w = 360;
	screen.wins[5].win_h = 360;

	ret = disp_init_pro(&screen);
	if (ret) {
		printf("error func:%s, line:%d\n", __func__, __LINE__);
		goto exit1;
	}

	/* 3、提交显示 */
	g_run = 1;
	for(int i = 0; i < 6; i++){
		my_wins[i].win_num = i;
		pthread_create(&my_wins[i].th, NULL, disp_thread, &my_wins[i]);
	}

	while(g_run) {
		sleep(1);
	}

	for(int i = 0; i < 6; i++){
		pthread_join(my_wins[i].th, NULL);
	}

	disp_exit_pro();
exit1:
	for(int i = 0; i < 6; i++){
		if(my_wins[i].pbuf){
			free(my_wins[i].pbuf);
			my_wins[i].pbuf = NULL;
		}
	}

    return ret;
}

