
#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <sys/time.h>
#include"OCRDetection.h"
#include"OCRRecognition.h"

using namespace cv;
using namespace std;

int main(int argc, char **argv)
{
	/* 参数初始化 */
	const char *img_path = argv[1];
	Mat frame = imread(img_path);
	if (frame.empty()) {
		cout << "Error: Could not load image" << endl;
		return -1;
	}

	OCRDetection ocrDetection;
	OCRRecognition ocrRecognition;

	/* 算法模型初始化 */
	ocrDetection.initModel("OCRDetection.model");
	ocrRecognition.initModel("OCRRecognition.model", "./dict_text.txt");  

	/* 算法模型运行 */

	vector<ImgBox> crop_img;
	crop_img = ocrDetection.getTextImages(frame); 

	vector<StringBox> result;
	result = ocrRecognition.inference(crop_img);

	for (auto &txt : result) {                                                
		cout << txt.txt << "\n" << endl;
		/* 画框 */
		drawTextBox(frame, txt.txtPoint, 1);                        
		//cv::putText(frame, txt.txt, cv::Point(0, 50), FONT_HERSHEY_SCRIPT_SIMPLEX, 5, cv::Scalar(255, 255, 0));
	}

	cv::imwrite("result.jpg", frame);	

	return 0;
}

