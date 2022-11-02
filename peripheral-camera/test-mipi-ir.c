#include <stdio.h>
#include <unistd.h>
#include <signal.h>

#include <camera.h>

#define CAMERA_WIDTH	720
#define CAMERA_HEIGHT	1280
#define	IMGRATIO		3
#define	IMAGE_SIZE		(CAMERA_WIDTH*CAMERA_HEIGHT*IMGRATIO)

int main()
{
	char *pbuf = NULL;
	int ret = 0;
	int skip = 0;
	FILE *fp = NULL;

	ret = ircamera_init(CAMERA_WIDTH, CAMERA_HEIGHT, 90);
	if (ret) {
		printf("error: %s, %d\n", __func__, __LINE__);
		goto exit3;
	}

	pbuf = (char *)malloc(IMAGE_SIZE);
	if (!pbuf) {
		printf("error: %s, %d\n", __func__, __LINE__);
		ret = -1;
		goto exit2;
	}

	//跳过前10帧
	skip = 10;
	while(skip--) {
		ret = ircamera_getframe(pbuf);
		if (ret) {
			printf("error: %s, %d\n", __func__, __LINE__);
			goto exit1;
		}
	}

	/* tips: 可以在Ubuntu下用mplayer播放录制图像
	*	adb pull /tmp/photo
	*	mplayer -demuxer rawvideo -rawvideo w=720:h=1280:format=bgr24 photo -loop 0
	*/
	fp = fopen("/tmp/photo", "w");
	if (!fp) {
		printf("error: %s, %d\n", __func__, __LINE__);
		ret = -1;
		goto exit2;
	}
	fwrite(pbuf, 1, IMAGE_SIZE, fp);
	fclose(fp);

exit1:
	free(pbuf);
	pbuf = NULL;
exit2:
	ircamera_exit();
exit3:
    return ret;
}
