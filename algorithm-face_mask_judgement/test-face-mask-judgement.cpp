#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <fstream>
#include <atomic>
#include <queue>
#include <thread>
#include <mutex>
#include <chrono>
#include <sys/time.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>

#include <opencv2/opencv.hpp>

#include <unistd.h>
#include <sys/syscall.h>
#include "face_mask_judgement.h"

using namespace std;
using namespace cv;

double what_time_is_it_now()
{
    struct timeval time;
    if (gettimeofday(&time,NULL)){
        return 0;
    }
    return (double)time.tv_sec + (double)time.tv_usec * .000001;
}


int main(int argc, char **argv)
{

	if( argc != 2)
	{
		printf("./test-face-mask-judgement xxx.jpg \n");
		return -1;
	}

	rknn_context ctx;
	float result[2];
	int ret;
	double start_time,end_time;

	cv::Mat src_1;
	src_1 = cv::imread(argv[1], 1);

	/* 人脸戴口罩判断初始化 */
	ret = face_mask_judgement_init(&ctx, "./face_mask_judgement.model");
	if( ret < 0)
	{
		printf("face_mask_judgement_init fail! ret=%d\n", ret);
		return -1;
	}

	start_time = what_time_is_it_now();

	/* 人脸戴口罩判断运行 */
	face_mask_judgement_run(ctx, &src_1, result);
	printf("normal_face possibility:%f\n", result[0]);
	printf("masked_face possibility:%f\n", result[1]);

	end_time = what_time_is_it_now();
	printf("run used time: %f\n", end_time-start_time);

	/* 人脸戴口罩判断释放 */
	face_mask_judgement_release(ctx);

}

