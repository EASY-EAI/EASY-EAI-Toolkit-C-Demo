
#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include "face_detect.h"
#include "face_alignment.h"
#include "face_recognition.h"


using namespace cv;


int main(int argc, char **argv)
{
	rknn_context detect_ctx, recognition_ctx;
	std::vector<det> result1, result2;
	int ret;
	struct timeval start;
	struct timeval end;
	float time_use=0;


	if( argc != 3)
	{
		printf("./face_recognition_demo xxx.jpg xxx.jpg\n");
		return -1;
	}

	cv::Mat src_1, src_2;
	src_1 = cv::imread(argv[1], 1);
	src_2 = cv::imread(argv[2], 1);

	/* 人脸检测初始化 */	
	printf("face detect init!\n");
	ret = face_detect_init(&detect_ctx, "./face_detect.model");
	if( ret < 0)
	{
		printf("face_detect_init fail! ret=%d\n", ret);
		return -1;
	}

	/* 人脸识别初始化 */
	printf("face recognition init!\n");
	ret =  face_recognition_init(&recognition_ctx, "./face_recognition.model");
	if( ret < 0)
	{
		printf("face_recognition fail! ret=%d\n", ret);
		return -1;
	}

	/* 人脸检测执行 */
	face_detect_run(detect_ctx, src_1, result1);
	face_detect_run(detect_ctx, src_2, result2);

	Point2f points1[5], points2[5];

	for (int j = 0; j < (int)result1[0].landmarks.size(); ++j) 
	{
		points1[j].x = (int)result1[0].landmarks[j].x;
		points1[j].y = (int)result1[0].landmarks[j].y;
	}

	for (int j = 0; j < (int)result2[0].landmarks.size(); ++j) 
	{
		points2[j].x = (int)result2[0].landmarks[j].x;
		points2[j].y = (int)result2[0].landmarks[j].y;
	}

	Mat face_algin_1, face_algin_2;
	face_algin_1 = face_alignment(src_1, points1);
	face_algin_2 = face_alignment(src_2, points2);


	/* 人脸识别执行 */
	float feature_1[512], feature_2[512];

	gettimeofday(&start,NULL); 
	face_recognition_run(recognition_ctx, &face_algin_1, &feature_1);
	gettimeofday(&end,NULL);
	time_use=(end.tv_sec-start.tv_sec)*1000000+(end.tv_usec-start.tv_usec);//微秒
	printf("time_use is %f\n",time_use/1000);

	face_recognition_run(recognition_ctx, &face_algin_2, &feature_2);


	float similarity;
	similarity = face_recognition_comparison(feature_1, feature_2, 512);

	printf("similarity:%f\n", similarity);	

	/* 人脸检测释放 */
	face_detect_release(detect_ctx);

	/* 人脸识别释放 */
	face_recognition_release(recognition_ctx);

	return 0;
}

