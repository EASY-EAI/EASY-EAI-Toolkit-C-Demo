#include <stdio.h>
#include <unistd.h>
#include <signal.h>

#include <disp.h>
#include <rga/RgaApi.h>

#define	DISP_WIDTH		720
#define	DISP_HEIGHT		1280
#define	IMAGE_PATH		"720X1280.rgb"
#define	IMGRATIO		3
#define	IMAGE_SIZE		(DISP_WIDTH*DISP_HEIGHT*IMGRATIO)

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
	ret = disp_init(DISP_WIDTH, DISP_HEIGHT); //RGB888 default
	if (ret) {
		printf("disp_init() error func:%s, line:%d\n", __func__, __LINE__);
		goto exit1;
	}

	/* 3、提交显示 */
	disp_commit(pbuf, IMAGE_SIZE);

	g_run++;
	while(g_run) {
		sleep(1);
	}

	disp_exit();
exit1:
	free(pbuf);
	pbuf = NULL;

    return 0;
}

