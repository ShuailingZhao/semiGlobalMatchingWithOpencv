#include"opencv2/opencv.hpp"
namespace stereoMatch{	
	enum { STEREO_BM = 0, STEREO_SGBM = 1, STEREO_HH = 2, STEREO_VAR = 3, STEREO_3WAY = 4 };
 
 
	void calDispWithSGBM(cv::Mat Img_L, cv::Mat Img_R, cv::Mat &imgDisparity8U)
	{
		cv::Size imgSize = Img_L.size();
		int numberOfDisparities = ((imgSize.width / 8) + 15) & -16;
		cv::Ptr<cv::StereoSGBM> sgbm = cv::StereoSGBM::create(0, 16, 3);

		int cn = Img_L.channels();//左图像的通道数
		int SADWindowSize = 9;
		int sgbmWinSize = SADWindowSize > 0 ? SADWindowSize : 3;
		sgbm->setMinDisparity(0);//minDisparity最小视差默认为0；
		sgbm->setNumDisparities(numberOfDisparities);//numDisparity视差搜索范围，其值必须为16的整数倍；
		sgbm->setP1(8 * cn*sgbmWinSize*sgbmWinSize);
		sgbm->setP2(32 * cn*sgbmWinSize*sgbmWinSize);//一般建议惩罚系数P1、P2取此两值，P1、P2控制视差图的光滑度,P2越大，视差图越平滑
		sgbm->setDisp12MaxDiff(1);//左右一致性检测最大容许误差阈值
		sgbm->setPreFilterCap(31);//预处理滤波器的截断值，预处理的输出值仅保留[-preFilterCap, preFilterCap]范围内的值，参数范围：1 - 31
		sgbm->setUniquenessRatio(10);//视差唯一性百分比：视差窗口范围内最低代价是次低代价的(1 + uniquenessRatio/100)倍时
					     //最低代价对应的视差值才是该像素点的视差，否则该像素点的视差为 0 ，不能为负值，一般去5——15
		sgbm->setSpeckleWindowSize(100);//视差连通区域像素点个数的大小：对于每一个视差点，当其连通区域的像素点个数小于,
						//speckleWindowSize时，认为该视差值无效，是噪点。
		sgbm->setSpeckleRange(32);	//视差连通条件：在计算一个视差点的连通区域时，当下一个像素点视差变化绝对值大于
						//speckleRange就认为下一个视差像素点和当前视差像素点是不连通的。
		sgbm->setMode(0);                                 //模式选择
		sgbm->setBlockSize(sgbmWinSize);                  //设置SAD代价计算窗口，一般在3*3到21*21之间
				                            //blockSize(SADWindowSize) 越小，也就是匹配代价计算的窗口越小，视差图噪声越大；
				                            //blockSize越大，视差图越平滑；
				                            //太大的size容易导致过平滑，并且误匹配增多，体现在视差图中空洞增多


		//三种模式选择（HH、SGBM、3WAY）
		int algorithm = STEREO_SGBM;
		if (algorithm == STEREO_HH)
		sgbm->setMode(cv::StereoSGBM::MODE_HH);
		else if (algorithm == STEREO_SGBM)
		sgbm->setMode(cv::StereoSGBM::MODE_SGBM);
		else if (algorithm == STEREO_3WAY)
		sgbm->setMode(cv::StereoSGBM::MODE_SGBM_3WAY);
		cv::Mat imgDisparity16S = cv::Mat(Img_L.rows, Img_L.cols, CV_16S);
		sgbm->compute(Img_L, Img_R, imgDisparity16S);
		//--Display it as a CV_8UC1 image：16位有符号转为8位无符号
		imgDisparity16S.convertTo(imgDisparity8U, CV_8U, 255 / (numberOfDisparities*16.));
	}

}
