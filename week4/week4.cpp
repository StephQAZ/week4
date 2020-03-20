﻿// week4.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int main()
{
	cv::Mat srcMat = imread("C:\\Users\\27318\\Desktop\\大二下网络课程\\数字图像\\第四周\\clip.png", 0);
	cv::Mat binaryMat, labelMat, statsMat, centrMat;
	cv::Mat dstMat;

	/*二值化*/
	threshold(srcMat, dstMat, 0, 200, THRESH_OTSU);
	imshow("binary", dstMat);

	//Mat kernel = getStructuringElement(MORPH_CROSS, Size(12, 12));
	//dilate(binaryMat, dstMat, kernel);
	//imshow("dilate", dstMat);

	int nComp = connectedComponentsWithStats(dstMat,
		labelMat,
		statsMat,
		centrMat,
		8,
		CV_32S);


	for (int i = 1; i < nComp; i++) {
		Rect bndbox;
		bndbox.x = statsMat.at<int>(i, 0);
		bndbox.y = statsMat.at<int>(i, 1);
		bndbox.width = statsMat.at<int>(i, 2);
		bndbox.height = statsMat.at<int>(i, 3);
		rectangle(dstMat, bndbox, CV_RGB(255, 255, 255), 1, 8, 0);
	}

	imshow("output", dstMat);
	nComp--;
	cout << "个数：" << nComp << endl;


	waitKey(0);
	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
