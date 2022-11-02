#ifndef BODY_POSE_DETECT_POSTPROCESS_H
#define BODY_POSE_DETECT_POSTPROCESS_H

#include <stdint.h>


struct KeyPoint{
	KeyPoint(cv::Point point, float probability){
		this->id = -1;
		this->point = point;
		this->probability = probability;
	}

	int id;
	cv::Point point;
	float probability;
};

inline std::ostream& operator << (std::ostream& os, const KeyPoint& kp)
{
	os << "Id:" << kp.id << ", Point:" << kp.point << ", Prob:" << kp.probability << std::endl;
	return os;
}


struct ValidPair{
	ValidPair(int aId,int bId,float score){
		this->aId = aId;
		this->bId = bId;
		this->score = score;
	}

	int aId;
	int bId;
	float score;
};

inline std::ostream& operator << (std::ostream& os, const ValidPair& vp)
{
	os << "A:" << vp.aId << ", B:" << vp.bId << ", score:" << vp.score << std::endl;
	return os;
}


template < class T > inline std::ostream& operator << (std::ostream& os, const std::vector<T>& v)
{
    os << "[" << "\n" << " ";
	bool first = true;
    for (typename std::vector<T>::const_iterator ii = v.begin(); ii != v.end(); ++ii, first = false)
    {
		if(!first) 
		    os << " ";
        os << " " << *ii;
    }os << "]";
    return os;
}

template < class T > inline std::ostream& operator << (std::ostream& os, const std::set<T>& v)
{
    os << "[";
	bool first = true;
    for (typename std::set<T>::const_iterator ii = v.begin(); ii != v.end(); ++ii, first = false)
    {
		if(!first) os << ",";
        os << " " << *ii;
    }
    os << "]";
    return os;
}

/* 
 * 姿态估计后处理函数
 * imgDst:输入图片,netOutputParts:对rknn的推理结果进行切片后的矩阵
 * (imgOldWidth,imgOldHeight):imgDst的尺寸
 */
void body_pose_post_process(cv::Mat imgDst, const std::vector<cv::Mat>& netOutputParts, int imgOldWidth, int imgOldHeight, std::vector<KeyPoint>& keyPointsList, std::vector<std::vector<KeyPoint>>& detectedKeypoints, std::vector<std::vector<int>>& personwiseKeypoints);

#endif //_RKNN_ZERO_COPY_DEMO_POSTPROCESS_H_
