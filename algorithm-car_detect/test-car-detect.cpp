
#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <sys/time.h>
#include"car_detect.h"

using namespace cv;
using namespace std;

static Scalar colorArray[10]={
    Scalar(255, 0, 0, 255),
    Scalar(0, 255, 0, 255),
    Scalar(0,0,139,255),
    Scalar(0,100,0,255),
    Scalar(139,139,0,255),
    Scalar(209,206,0,255),
    Scalar(0,127,255,255),
    Scalar(139,61,72,255),
    Scalar(0,255,0,255),
    Scalar(255,0,0,255),
};

int plot_one_box(Mat src, int x1, int x2, int y1, int y2, char *label, char colour)
{
    int tl = round(0.002 * (src.rows + src.cols) / 2) + 1;
    rectangle(src, cv::Point(x1, y1), cv::Point(x2, y2), colorArray[(unsigned char)colour], 3);

    int tf = max(tl -1, 1);

    int base_line = 0;
    cv::Size t_size = getTextSize(label, FONT_HERSHEY_SIMPLEX, (float)tl/3, tf, &base_line);
    int x3 = x1 + t_size.width;
    int y3 = y1 - t_size.height - 3;

    rectangle(src, cv::Point(x1, y1), cv::Point(x3, y3), colorArray[(unsigned char)colour], -1);
    putText(src, label, cv::Point(x1, y1 - 2), FONT_HERSHEY_SIMPLEX, (float)tl/3, cv::Scalar(255, 255, 255, 255), tf, 8);
    return 0;
}

int main(int argc, char **argv)
{
	/* 参数初始化 */
	car_detect_result_group_t detect_result_group;

	/* 算法模型初始化 */
	rknn_context ctx;
	car_detect_init(&ctx, "./car_detect.model");

	/* 算法运行 */
	cv::Mat src;
	src = cv::imread("test.jpg", 1);

	struct timeval start;
	struct timeval end;
	float time_use=0;

	gettimeofday(&start,NULL); 
	car_detect_run(ctx, src, &detect_result_group);

	gettimeofday(&end,NULL);
	time_use=(end.tv_sec-start.tv_sec)*1000000+(end.tv_usec-start.tv_usec);//微秒
	printf("time_use is %f\n",time_use/1000);

	/* 算法结果在图像中画出并保存 */
	for (int i = 0; i < detect_result_group.count; i++)
	{
		car_detect_result_t *det_result = &(detect_result_group.results[i]);
		
		/*
		if( det_result->prop < 0.3 )
		{
			continue;
		}
		*/

		printf("%s @ (%d %d %d %d) %f\n",
			   det_result->name,
			   det_result->box.left, det_result->box.top, det_result->box.right, det_result->box.bottom,
			   det_result->prop);
		int x1 = det_result->box.left;
		int y1 = det_result->box.top;
		int x2 = det_result->box.right;
		int y2 = det_result->box.bottom;
		
		char label_text[50];
		memset(label_text, 0 , sizeof(label_text));
		sprintf(label_text, "%s %0.2f",det_result->name, det_result->prop); 
		plot_one_box(src, x1, x2, y1, y2, label_text, i%10);
	}    

	cv::imwrite("result.jpg", src);	


	/* 算法模型空间释放 */
	car_detect_release(ctx);

	return 0;
}

