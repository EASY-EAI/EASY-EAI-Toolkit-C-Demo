
#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <sys/time.h>

#include "self_learning.h"

using namespace cv;
using namespace std;


int main(int argc, char **argv)
{

	rknn_context classify_ctx;
	self_learning_init(&classify_ctx, "./classify.model");

	const int k_value = 3;
	struct self_learning_data train_data[50];
	int train_data_count = 0;
	memset(train_data, 0, 50*sizeof(struct self_learning_data));


	//加载训练图像
	char image_name[128] = { 0 };
	for (int i = 1; i <= 3; i++)
	{
		for(int j = 1; j <=5; j++)
		{
			sprintf(image_name, "train/%d/%d.jpg", i, j);
			Mat train_image = imread(image_name, 1);

			self_learning_train(classify_ctx, train_image, train_data+train_data_count, i);
			train_data_count++;
		}
	}

	//测试图像
	for (int i = 1; i <= 4; i++)
	{
		sprintf(image_name, "test/1/%d.jpg", i);
		Mat test_image = imread(image_name, 1);
		int result;
		result = self_learning_inference(classify_ctx, test_image, train_data, train_data_count, k_value);
		printf("result:%d\n", result);
		
	}
	
	self_learning_release(classify_ctx);

	return 0;
}
