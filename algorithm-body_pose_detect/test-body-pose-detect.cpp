
#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <sys/time.h>
#include <iostream>
#include <random>
#include"body_pose_detect.h"

/*** 骨骼点对应顺序 ***/
unsigned char keypointsMapping[18][30] = {
	"Nose", "Neck",	"R-Sho", "R-Elb", "R-Wr", "L-Sho", "L-Elb", "L-Wr",	"R-Hip", "R-Knee", "R-Ank",	"L-Hip", "L-Knee", "L-Ank",	"R-Eye", "L-Eye", "R-Ear", "L-Ear"
};

const std::vector<std::pair<int,int>> posePairs = {     //骨骼点配对逻辑
	{1,2}, {1,5}, {2,3}, {3,4}, {5,6}, {6,7},
	{1,8}, {8,9}, {9,10}, {1,11}, {11,12}, {12,13},
	{1,0}, {0,14}, {14,16}, {0,15}, {15,17}, {2,17},
	{5,16}
};

void populateColorPalette(std::vector<cv::Scalar>& colors,int nColors){     //颜色填充函数
	std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis1(64, 200);
    std::uniform_int_distribution<> dis2(100, 255);
    std::uniform_int_distribution<> dis3(100, 255);

	for(int i = 0; i < nColors;++i){
		colors.push_back(cv::Scalar(dis1(gen),dis2(gen),dis3(gen)));
	}
}

int main(int argc, char **argv)
{

	if( argc != 2)
	{
		printf("./test-body-pose-detect xxx.jpg \n");
		return -1;
	}

	/* 参数初始化 */
	const int nPoints = 18;

	/* 算法运行 */
	cv::Mat src;
	src = cv::imread(argv[1], cv::IMREAD_COLOR);

	//while(capture.read(src)){


	/* 算法模型初始化 */
	rknn_context ctx;
	body_pose_detect_init(&ctx, "./body_pose_detect.model");

	/* 算法结果在图像中画出并保存 */
	std::vector<std::vector<KeyPoint_body>> detectedKeypoints;   //按组存放检测出的各部位keypoints关节点
	std::vector<KeyPoint_body> keyPointsList;    //将detectedKeypoints依次存入keyPointsList
	std::vector<std::vector<int>> personwiseKeypoints;      //按骨骼顺序给keypoints配对

	body_pose_detect_run(ctx, src, keyPointsList, detectedKeypoints, personwiseKeypoints);

	std::vector<cv::Scalar> colors;
	populateColorPalette(colors, nPoints);       //给各个关节点上色

	int i,j;

	for(i = 0; i < nPoints; i++)
	{        
		//画出关节点
		for(j = 0; j < detectedKeypoints[i].size(); j++)
		{
			float scales_x;
			float scales_y;
			scales_x = (float)src.cols/368;
			scales_y = (float)src.rows/368;

			printf("[ID:%d %s,probability:%f x:%d, y:%d]\n", detectedKeypoints[i][j].id, keypointsMapping[detectedKeypoints[i][j].id], detectedKeypoints[i][j].probability, detectedKeypoints[i][j].point.x, detectedKeypoints[i][j].point.y);
			/*
			if( detectedKeypoints[i][j].id == 0)
			{
				cv::circle(src, cv::Point( detectedKeypoints[i][j].point.x * scales_x, detectedKeypoints[i][j].point.y * scales_y), 4, colors[i], -1, cv::LINE_AA);
			}
			*/
			cv::circle(src, cv::Point( detectedKeypoints[i][j].point.x * scales_x, detectedKeypoints[i][j].point.y * scales_y), 4, colors[i], -1, cv::LINE_AA);
			
		}
	}

	
	for(int i=0;i<nPoints-1;++i){       //绘制骨骼
		for(int n=0;n<personwiseKeypoints.size();++n){
			const std::pair<int,int>& posePair = posePairs[i];
			
			int indexA= personwiseKeypoints[n][posePair.first];
			int indexB= personwiseKeypoints[n][posePair.second];
			
			if(indexA==-1||indexB==-1){
				continue;
			}
			
			const KeyPoint_body& kpA=keyPointsList[indexA];
			const KeyPoint_body& kpB=keyPointsList[indexB];
			
			std::cout<<"kpA = "<<kpA<<"kpB = "<<kpB<<std::endl;
			
			float scales_x;
			float scales_y;

			scales_x = (float)src.cols/368;
			scales_y = (float)src.rows/368;

			cv::line(src, cv::Point(kpA.point.x * scales_x, kpA.point.y * scales_y), cv::Point(kpB.point.x * scales_x, kpB.point.y * scales_y), colors[i],3,cv::LINE_AA);
		}
	}
	

	cv::imwrite("result.jpg", src);

	/* 算法模型空间释放 */
	body_pose_detect_release(ctx);
	return 0;
}

