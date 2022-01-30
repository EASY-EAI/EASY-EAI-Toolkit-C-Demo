
#include <opencv2/opencv.hpp>
#include <stdio.h>

#include "qrdecode.h"

using namespace cv;


int main(int argc, char **argv)
{
	if( argc != 2)
	{
		printf("./test-qrdecode xxx\n");
		return -1;
	}

	Mat image;
	image = cv::imread(argv[1], 1);	

	struct qrcode_info info;
	qr_decode(image, &info);

	printf("x1:%d\n", info.x1);
	printf("x2:%d\n", info.x2);
	printf("y1:%d\n", info.y1);
	printf("y2:%d\n", info.y2);
	printf("type:%s\n", info.type);
	printf("result:%s\n", info.result);

	rectangle(image, Point(info.x1, info.y1), Point(info.x2, info.y2), Scalar(0, 255, 0), 3);

	imwrite("result.jpg", image);

    return 0;
}

