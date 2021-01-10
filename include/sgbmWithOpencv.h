#ifndef SGBMWITHOPENCV_H
#define SGBMWITHOPENCV_H

#include "opencv2/core.hpp"
#include <opencv2/core/utility.hpp>
#include <cctype>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <iostream>
#include <opencv2/calib3d.hpp>
namespace stereoMatch
{
	void calDispWithSGBM(cv::Mat Img_L, cv::Mat Img_R, cv::Mat &imgDisparity8U);


}
#endif


