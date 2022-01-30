#include <stdio.h>
#include <unistd.h>
#include <signal.h>

#include <disp.h>
#include <rga/RgaApi.h>

#define	DISP_WIDTH		720
#define	DISP_HEIGHT		1280
#define	DISP_XOFF		0
#define	DISP_YOFF		0
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

	ret = disp_init(DISP_WIDTH, DISP_HEIGHT); //RGB888 default
	if (ret) {
		printf("error func:%s, line:%d\n", __func__, __LINE__);
		goto exit1;
	}

	pbuf = (char *)malloc(IMAGE_SIZE);
	if (!pbuf) {
		printf("error: %s, %d\n", __func__, __LINE__);
		ret = -1;
		goto exit2;
	}

	fp = fopen(IMAGE_PATH, "r");
	if (!fp) {
		printf("error: %s, %d\n", __func__, __LINE__);
		ret = -1;
		goto exit3;
	}

	ret = fread(pbuf, 1, IMAGE_SIZE, fp);
	if (ret == IMAGE_SIZE) {
		disp_commit(pbuf, DISP_XOFF, DISP_YOFF);
	}
	else {
		printf("error: %s, %d\n", __func__, __LINE__);
		ret = -1;
	}

	g_run++;
	while(g_run) {
		sleep(1);
	}

	fclose(fp);
exit3:
	free(pbuf);
	pbuf = NULL;
exit2:
	disp_exit();
exit1:
    return ret;
}

