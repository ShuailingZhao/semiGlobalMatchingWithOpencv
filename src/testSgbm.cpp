#include <iostream>
#include "opencv2/opencv.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include"sgbmWithOpencv.h"


void getParserInfo(std::string& leftImg, std::string& rightImg, int argc, char** argv)
{
	cv::CommandLineParser parser(argc, argv, "{help||}{lI|../Data/Cloth3/view1.png|left image}"
                             "{rI|../Data/Cloth3/view5.png|right image}");

	leftImg = parser.get<std::string>("lI");
	rightImg = parser.get<std::string>("rI");
}

const char * usage = 
"\n"
"./testSgbm -lI=../data/Cloth3/view1.png -rI=../data/Cloth3/view5.png"
"\n";

static void help()
{
	std::cout << usage;
}

int main(int argc, char** argv)
{
	if(argc<2)
	{
		help();
		return 0;
	}
	std::string leftImg, rightImg;
	getParserInfo(leftImg, rightImg, argc, argv);
	cv::Mat Img_L = cv::imread(leftImg, 0);
	cv::Mat Img_R = cv::imread(rightImg, 0);
	
	cv::Mat Disparity8U = cv::Mat(Img_L.rows, Img_R.cols, CV_8UC1);//创建一个Disparity图像


	stereoMatch::calDispWithSGBM(Img_L, Img_R, Disparity8U);
	cv::imshow("Teddy_L", Img_L);
	cv::imshow("Teddy_R", Img_R);
	cv::imshow("Disparity", Disparity8U);


	cv::waitKey();
	system("pause");  //按任意键退出
	return 0;
}

