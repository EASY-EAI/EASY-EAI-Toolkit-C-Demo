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
#include "face_detect.h"
#include "face_alignment.h"
#include "face_landmark98.h"

using namespace std;
using namespace cv;



int main(int argc, char **argv)
{

	if( argc != 2)
	{
		printf("./test-face-landmark98 xxx.jpg \n");
		return -1;
	}

	rknn_context detect_ctx, landmark_ctx;
	std::vector<det> result;
	int ret;

	cv::Mat src;
	src = cv::imread(argv[1], 1);


	face_detect_init(&detect_ctx, "./face_detect.model");

	/* 人脸关键点定位初始化 */
	ret = face_landmark98_init(&landmark_ctx, "./face_landmark98.model");
	if( ret < 0)
	{
		printf("face_mask_judgement_init fail! ret=%d\n", ret);
		return -1;
	}



	face_detect_run(detect_ctx, src, result);

	printf("face num:%d\n",result.size());

	for (int i = 0; i < (int)result.size(); i++)
	{
		int x = (int)(result[i].box.x);
		int y = (int)(result[i].box.y);
		int w = (int)(result[i].box.width);
		int h = (int)(result[i].box.height);
		int max = (w > h)?w:h;

		// 判断图像裁剪是否越界
		if( ((x +max) > src.cols) || ((y +max) > src.rows) )
		{
			continue;
		}
		

		cv::Mat roi_img, reize_img;
		roi_img = src(cv::Rect(x, y, max,max));
        roi_img = roi_img.clone();

		resize(roi_img, reize_img, Size(256,256), 0, 0, INTER_AREA);
		float ratio;
		ratio = (float)max/256;

		std::vector<KeyPointType> keyPoints;
		face_landmark98_run(landmark_ctx, &reize_img, &keyPoints);

		for(int n = 0; n < 98; n++)
		{
			//cout<<"keyPoints "<< n <<" :"<< keyPoints[n].point.x*ratio +x <<","<< keyPoints[n].point.y*ratio +y <<endl;
			cv::circle(src, Point( keyPoints[n].point.x*ratio+x, keyPoints[n].point.y*ratio+y), 2, cv::Scalar(0, 255, 0), 2);
		}

	}

	cv::imwrite("result.jpg", src);

	/* 人脸检测释放 */
	face_detect_release(detect_ctx);

	/* 人脸关键点定位释放 */
	face_landmark98_release(landmark_ctx);

	return 0;
}

