
#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <sys/time.h>
#include "moving_detect.h"

using namespace cv;


int main(int argc, char **argv)
{

	if( argc != 3)
	{
		printf("./test-moving-detect xxx.jpg xxx.jpg\n");
		return -1;
	}

	struct timeval start;
	struct timeval end;
	float time_use=0;


	Mat image_1, image_2;
	image_1 = cv::imread(argv[1], 1);	
	image_2 = cv::imread(argv[2], 1);

	moving_detect_result_group_t moving_detect_result;

	memset(&moving_detect_result, 0, sizeof(moving_detect_result_group_t));

	gettimeofday(&start,NULL);
	moving_detect(image_1, image_2, &moving_detect_result, 5);

	gettimeofday(&end,NULL);
	time_use=(end.tv_sec-start.tv_sec)*1000000+(end.tv_usec-start.tv_usec);//微秒
	printf("time_use is %f\n",time_use/1000);

	printf("moving_detect_result.count:%d\n", moving_detect_result.count);

	Mat result_frame;
	result_frame = image_1.clone();
	for( int i=0; i < moving_detect_result.count; i++ )
	{
		rectangle(result_frame, Point(moving_detect_result.results[i].left, moving_detect_result.results[i].top), Point(moving_detect_result.results[i].right, moving_detect_result.results[i].bottom), Scalar(0, 255, 0), 2, 8, 0);
	}

	imwrite("result_frame.jpg", result_frame);

    return 0;
}

