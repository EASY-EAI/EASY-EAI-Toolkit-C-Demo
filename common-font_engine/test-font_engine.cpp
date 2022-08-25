#include <opencv2/opencv.hpp>

#include <sys/time.h>

#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "font_engine.h"

int main(void)
{
	// 初始化字体透明度和颜色
	FontColor color = {200, 135, 189, 67};    // {A, R, G, B};
	
	// 初始化语言环境
	font_engine_init("./simhei.ttf", "zh_CN.utf8");
	
	// 读取底图
	cv::Mat img = cv::imread("./testPic.png");
	
	// 写入文字
	font_engine_set_fontSize(80);
	font_engine_putText(img.data, img.cols, img.rows, "欢迎使用", 210, 940, color);
	font_engine_set_fontSize(40);
	font_engine_putText(img.data, img.cols, img.rows, "欢迎使用", 290, 1020, color);
	
	// 保存写入文字后的底图
	cv::imwrite("./res.jpg", img);
	
	// 释放语言环境
	font_engine_unInit();
	
	return 0;
}
