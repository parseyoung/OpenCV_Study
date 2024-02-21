// cv::Mat types CV_8UC1, CV_8UC2, CV_8UC3, CV_8UC4
// Data Typeº° Æ¯Â¡

#include <opencv2/opencv.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
using namespace std;
using namespace cv;

int main() {

	Mat _8ucl = Mat::zeros(Size(3, 4), CV_8UC1);
	//Mat _8ucl = imread("C:/Users/woowon/Desktop/psy/house.jpg", IMREAD_GRAYSCALE);
	
	_8ucl.at<uchar>(cv::Point(1, 1)) = 120;
	cout << _8ucl << endl;
	cout << _8ucl.depth() << endl;
	cout << _8ucl.type() << endl;

	cout << _8ucl.size() << endl;
	cout << _8ucl.cols << endl;
	cout << _8ucl.rows << endl;
	cout << _8ucl.channels() << endl; // 1

	//namedWindow("8UC", 0);
	//imshow("8UC", _8ucl);
	//waitKey(0);
	return 0;
}