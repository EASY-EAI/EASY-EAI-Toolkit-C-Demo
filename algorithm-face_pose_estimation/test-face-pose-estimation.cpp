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
#include "face_pose_estimation.h"

using namespace std;
using namespace cv;

int plot_one_box(Mat src, int x1, int x2, int y1, int y2, char *label, char colour)
{
    int tl = round(0.002 * (src.rows + src.cols) / 2) + 1;
    rectangle(src, cv::Point(x1, y1), cv::Point(x2, y2), Scalar(255, 0, 0, 255), 3);

    int tf = max(tl -1, 1);

    int base_line = 0;
    cv::Size t_size = getTextSize(label, FONT_HERSHEY_SIMPLEX, (float)tl/3, tf, &base_line);
    int x3 = x1 + t_size.width;
    int y3 = y1 - t_size.height - 3;

    rectangle(src, cv::Point(x1, y1), cv::Point(x3, y3), Scalar(255, 0, 0, 255), -1);
    putText(src, label, cv::Point(x1, y1 - 2), FONT_HERSHEY_SIMPLEX, (float)tl/3, cv::Scalar(255, 255, 255, 255), tf, 8);
    return 0;
}

int main(int argc, char **argv)
{

	if( argc != 2)
	{
		printf("./test-face-pose-estimation xxx.jpg \n");
		return -1;
	}

	rknn_context detect_ctx, face_pose_estimation_ctx;
	std::vector<det> detect_result;
	int ret;
	struct timeval start;
	struct timeval end;
	float time_use=0;

	cv::Mat src;
	src = cv::imread(argv[1], 1);

	/* 人脸检测初始化 */
	ret = face_detect_init(&detect_ctx, "./face_detect.model");
	if( ret < 0)
	{
		printf("face_detect_init fail! ret=%d\n", ret);
		return -1;
	}

	/* 人脸姿态估计初始化 */
	ret = face_pose_estimation_init(&face_pose_estimation_ctx, "./face_pose_estimation.model");
	if( ret < 0)
	{
		printf("face_pose_estimation_init fail! ret=%d\n", ret);
		return -1;
	}

	/* 人脸检测执行 */
	face_detect_run(detect_ctx, src, detect_result);

	for( int i=0; i < (int)detect_result.size() ; i++ )
	{
		int x = (int)(detect_result[i].box.x);
		int y = (int)(detect_result[i].box.y);
		int w = (int)(detect_result[i].box.width);
		int h = (int)(detect_result[i].box.height);
		int max = (w > h)?w:h;

		// 判断图像裁剪是否越界
		if( ((x +max) > src.cols) || ((y +max) > src.rows) )
		{
			continue;
		}
		

		cv::Mat roi_img, reize_img, reize_img_rgb;
		roi_img = src(cv::Rect(x, y, max,max));
		roi_img = roi_img.clone();

		resize(roi_img, reize_img, Size(224,224), 0, 0, INTER_AREA);
		cvtColor(reize_img, reize_img_rgb, COLOR_BGR2RGB);

		/* 人脸姿态估计运行 */
		float pose_result[3];
		gettimeofday(&start,NULL); 
		face_pose_estimation_run(face_pose_estimation_ctx, &reize_img_rgb, pose_result);
		gettimeofday(&end,NULL);
		time_use=(end.tv_sec-start.tv_sec)*1000000+(end.tv_usec-start.tv_usec);//微秒
		printf("time_use is %f\n",time_use/1000);

		printf("yaw(偏航角):%f, pitch(俯仰角):%f, roll(翻滚角):%f\n", pose_result[0], pose_result[1], pose_result[2]);

		char label_text[100];
		memset(label_text, 0 , sizeof(label_text));
		sprintf(label_text, "yaw:%0.2f pitch:%0.2f roll:%0.2f", pose_result[0], pose_result[1], pose_result[2]); 
		plot_one_box(src, x, x+w, y, y+h, label_text, i%10);

	}

	imwrite("result.jpg", src);

	/* 人脸检测释放 */
	face_detect_release(detect_ctx);

	/* 人脸姿态估计释放 */
	face_pose_estimation_release(face_pose_estimation_ctx);

	return 0;
}

