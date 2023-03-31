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
#include "face_detect.h"
#include "face_alignment.h"
#include "face_mask_judgement.h"

using namespace std;
using namespace cv;

int main(int argc, char **argv)
{

	struct timeval start;
	struct timeval end;
	float time_use=0;

	if( argc != 2)
	{
		printf("./test-face-mask-judgement xxx.jpg \n");
		return -1;
	}

	rknn_context detect_ctx, mask_judge_ctx;
	std::vector<det> detect_result;
	float mask_result[2];
	int ret;

	cv::Mat src;
	src = cv::imread(argv[1], 1);

	/* 人脸检测初始化 */
	ret = face_detect_init(&detect_ctx, "./face_detect.model");
	if( ret < 0)
	{
		printf("face_detect_init fail! ret=%d\n", ret);
		return -1;
	}

	/* 人脸戴口罩判断初始化 */
	ret = face_mask_judgement_init(&mask_judge_ctx, "./face_mask_judgement.model");
	if( ret < 0)
	{
		printf("face_mask_judgement_init fail! ret=%d\n", ret);
		return -1;
	}

	/* 人脸检测执行 */
	face_detect_run(detect_ctx, src, detect_result);

	for( int i=0; i < (int)detect_result.size() ; i++ )
	{
		Point2f points[5];
	
		for (int j = 0; j < (int)detect_result[i].landmarks.size(); ++j) 
		{
			points[j].x = (int)detect_result[i].landmarks[j].x;
			points[j].y = (int)detect_result[i].landmarks[j].y;
		}

		Mat face_algin;
		face_algin = face_alignment(src, points);

		/* 人脸戴口罩判断运行 */
		gettimeofday(&start,NULL); 
		face_mask_judgement_run(mask_judge_ctx, &face_algin, mask_result);
		gettimeofday(&end,NULL);
		time_use=(end.tv_sec-start.tv_sec)*1000000+(end.tv_usec-start.tv_usec);//微秒
		printf("person %d\n", i);
		printf("time_use is %f\n",time_use/1000);
		printf("normal_face possibility:%f\n", mask_result[0]);
		printf("masked_face possibility:%f\n", mask_result[1]);		
		
		int x = (int)(detect_result[i].box.x);
		int y = (int)(detect_result[i].box.y);
		int w = (int)(detect_result[i].box.width);
		int h = (int)(detect_result[i].box.height);

		if( mask_result[0] > 0.6 )
		{
			rectangle(src, Rect(x, y, w, h), Scalar(0, 0, 255), 2, 8, 0);
		}
		else
		{
			rectangle(src, Rect(x, y, w, h), Scalar(0, 255, 0), 2, 8, 0);
		}
	}

	imwrite("result.jpg", src);

	/* 人脸检测释放 */
	face_detect_release(detect_ctx);

	/* 人脸戴口罩判断释放 */
	face_mask_judgement_release(mask_judge_ctx);

	return 0;
}

