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
	
	// 创建全局字体
	global_font_create("./simhei.ttf", CODE_UTF8);
	
	// 读取底图
	cv::Mat img = cv::imread("./testPic.png");
	
	// 写入文字
	global_font_set_fontSize(80);
	putText(img.data, img.cols, img.rows, "欢迎使用", 210, 940, color);
	global_font_set_fontSize(40);
	putText(img.data, img.cols, img.rows, "欢迎使用", 290, 1020, color);
	
	// 保存写入文字后的底图
	cv::imwrite("./res.jpg", img);
	
	// 销毁全局字体
	global_font_destory();
	
	return 0;
}
