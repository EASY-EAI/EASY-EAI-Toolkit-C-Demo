#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <vector>
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
#include "face_landmark98.h"

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
		printf("./test-face-landmark98 xxx.jpg \n");
		return -1;
	}

	rknn_context landmark_ctx;
	int ret;
	double start_time,end_time;

	cv::Mat src;
	src = cv::imread(argv[1], 1);

	/* 人脸关键点定位初始化 */
	ret = face_landmark98_init(&landmark_ctx, "./face_landmark98.model");
	if( ret < 0)
	{
		printf("face_mask_judgement_init fail! ret=%d\n", ret);
		return -1;
	}

	printf("face landmark init ok!\n");

	start_time = what_time_is_it_now();

	/* 人脸关键点定位运行 */
	std::vector<KeyPointType> keyPoints;
	face_landmark98_run(landmark_ctx, &src, &keyPoints);

	end_time = what_time_is_it_now();
	printf("run used time: %f\n", end_time-start_time);


    for(int i = 0;i < 98;i++)
    {
        cout<<"keyPoints "<<i<<":"<<keyPoints[i].point<<endl;
        cv::circle(src, keyPoints[i].point, 2, cv::Scalar(0, 255, 0), 2);
    }

	cv::imwrite("result.jpg", src);

	/* 人脸关键点定位释放 */
	face_landmark98_release(landmark_ctx);

	return 0;
}

