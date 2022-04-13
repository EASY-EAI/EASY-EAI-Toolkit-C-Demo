#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>

#include <camera.h>

#define CAMERA_WIDTH	1280
#define CAMERA_HEIGHT	720
#define	IMGRATIO		3
#define	IMAGE_SIZE		(CAMERA_WIDTH*CAMERA_HEIGHT*IMGRATIO)
#define	CAM_NUM			2
#define	CAM_FPS			5

static int g_run = 0;
static void sigterm_handler(int sig) {
	fprintf(stderr, "signal %d\n", sig);
	g_run = 0;
}

static void *thread_start(void *arg)
{
    int cam_num = *(int *)arg;
    char *uargv = NULL;
	FILE *fp = NULL;
	char *pbuf;
	int ret;
	char path[64] = {0};

	pbuf = (char *)malloc(IMAGE_SIZE);
	if (!pbuf) {
		printf("error: %s, %d\n", __func__, __LINE__);
		ret = -1;
		goto exit;
	}

	while(g_run) {
		ret = usbcamera_getframe(USB2_0, cam_num, pbuf);
		if (ret) {
			printf("error: %s, %d\n", __func__, __LINE__);
			goto exit;
		}
	}

	/* tips: 可以在Ubuntu下用mplayer播放录制图像
	*	mplayer -demuxer rawvideo -rawvideo w=1280:h=720:format=rgb24 photo%d -loop 0
	*/
	sprintf(path, "/tmp/photo%d", cam_num);
	fp = fopen(path, "w");
	if (!fp) {
		printf("error: %s, %d\n", __func__, __LINE__);
		ret = -1;
		goto exit;
	}
	fwrite(pbuf, 1, IMAGE_SIZE, fp);
	fclose(fp);

exit:
	if(pbuf){
		free(pbuf);
		pbuf = NULL;
	}
    return uargv;
}

int main()
{
	int s;
	int ret = 0;
	pthread_t thread_id[CAM_NUM];
	int cam_num[4] = {1, 2, 3, 4};

	signal(SIGINT, sigterm_handler);

	g_run = 1;
	usbcamera_preset_fps(CAM_FPS);
	for(int i = 0; i < CAM_NUM; i++){
		ret = usbcamera_init(USB2_0, cam_num[i], CAMERA_WIDTH, CAMERA_HEIGHT, 0);
		if (ret) {
			printf("init bus: USB2_0, port:%d.\n", cam_num[i]);
			printf("error: %s, %d\n", __func__, __LINE__);
			goto exit1;
		}
	}

	for(int i = 0; i < CAM_NUM; i++){
		s = pthread_create(&thread_id[i], NULL, &thread_start, &cam_num[i]);
		if(s != 0){
			printf("error: %s, %d\n", __func__, __LINE__);
			goto exit2;
		}
	}

exit2:
	for(int i = 0; i < CAM_NUM; i++){
		pthread_join(thread_id[i], NULL);
	}
	for(int i = 0; i < CAM_NUM; i++){
		usbcamera_exit(USB2_0, cam_num[i]);
	}
exit1:
    return ret;
}

