// getRotationMatrix2D() : 이미지의 회전 변환 metrix 생성
// Mat getRotationMatrix2D(Point2f center, double angle, double scale);
// center : 회전의 중심점, angle : 회전 각도(반시계), scale : 크기 조절(기본값1)
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/types.hpp"
#include <iostream>
using namespace std;
using namespace cv;

int main() {

	int cnt = 1;
	while (cnt++)
	{
		Mat inputImg = imread("C:/Users/woowon/Desktop/psy/house.jpg");
		Mat outputImg = Mat::zeros(Size(inputImg.cols, inputImg.rows), inputImg.type());
		namedWindow("input", 0);
		namedWindow("output", 0);

		Point2f inpMat[3];
		Point2f outMat[3];

		inpMat[0] = Point2f(0.0, 0.0);
		inpMat[1] = Point2f(inputImg.cols, 0.0);
		inpMat[2] = Point2f(0.0, inputImg.rows);

		outMat[0] = Point2f(0.0, 100);
		outMat[1] = Point2f(250 + cnt, 50);
		outMat[2] = Point2f(90 - cnt, 260);

		Mat M = getAffineTransform(inpMat, outMat);

		cout << M << endl;

		cv::warpAffine(inputImg, outputImg, M, outputImg.size());
		Point2f center(inputImg.cols / 2, inputImg.rows / 2);
		double angle = -50;
		double scale = 1;

		Mat MM = getRotationMatrix2D(center, angle, scale);

		Mat dstMat;
		warpAffine(inputImg, dstMat, MM, inputImg.size());
		imshow("input", inputImg);
		imshow("output", dstMat);
		waitKey(0);

	}

	return 0;
}