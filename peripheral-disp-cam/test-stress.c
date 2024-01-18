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

#define SEC 1 //秒
#define FPS 25
int main()
{
	char *pRGBbuf = NULL;
	char *pIRbuf = NULL;
	int ret = 0;

	/* display init */
	ret = disp_init(DISP_WIDTH, DISP_HEIGHT); //BGR888 default
	if (ret) {
		printf("error func:%s, line:%d\n", __func__, __LINE__);
		goto exit1;
	}

	/* alloc buffer for cap data */
	pRGBbuf = (char *)malloc(IMAGE_SIZE);
	if (!pRGBbuf) {
		printf("error: %s, %d\n", __func__, __LINE__);
		ret = -1;
		goto exit2;
	}
	pIRbuf = (char *)malloc(IMAGE_SIZE);
	if (!pIRbuf) {
		printf("error: %s, %d\n", __func__, __LINE__);
		ret = -1;
		goto exit3;
	}

    for(int i = 0; i < 1000; i++){
        printf(">>>================================== the %d times init start \n", i);
    	/* camera init */
    	ret = rgbcamera_init(CAMERA_WIDTH, CAMERA_HEIGHT, 90);
        ret =  ircamera_init(CAMERA_WIDTH, CAMERA_HEIGHT, 90);
    	if (ret) {
    		printf("error func:%s, line:%d\n", __func__, __LINE__);
    	}
        /* display */
        for(int picNum = 0; picNum < SEC*FPS; picNum++){
    		/* capture */
    		ret = rgbcamera_getframe(pRGBbuf);
    		if (!ret) {
    			disp_commit(pRGBbuf, IMAGE_SIZE);
    		}
    		ret = ircamera_getframe(pIRbuf);
    	}
    	/* camera exit */
        rgbcamera_exit();
        ircamera_exit();

        //for(int sec = 0; sec<SEC; sec++){
        //    sleep(1);
        //}
    }
    
	free(pIRbuf);
	pIRbuf = NULL;
exit3:
	free(pRGBbuf);
	pRGBbuf = NULL;
exit2:
	disp_exit();
exit1:
    return ret;
}

