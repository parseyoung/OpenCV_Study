// opencv는 모듈별로 기능이 나누어져 있어 여러개의 헤더를 include 함
// #include <opencv2/opencv.hpp> : 하나만 include 하는 방법도 있음
// opencv와 c++는 충돌이 나는 라이브러리명이 없어 usingnamespace 사용 가능

// 이미지 다루기 // 

#include <opencv2/core.hpp> // opencv 기본 자료구조 및 함수
#include <opencv2/imgcodecs.hpp> // image read & save
#include <opencv2/highgui.hpp> // interface
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp> // canny function

// c++ headers
#include <iostream> 

using namespace std;
using namespace cv;

int main()
{
	Mat image;
	image = imread("house.jpg", IMREAD_GRAYSCALE);
	if (image.empty())
	{
		cout << "Could not open or find the i";
		return -1;
	}

	// second argument 
	// WINDOW_NORMAL : 이미지 크기 자유롭게 조정 가능
	// WND_PROP_FULLSCREEN : 전체 화면
	namedWindow("Original", WND_PROP_FULLSCREEN);
	setWindowProperty("Original", WND_PROP_FULLSCREEN, WINDOW_FULLSCREEN);
	imshow("Original", image);
	waitKey(0);

	Canny(image, image, 50, 150);
	namedWindow("Canny", WINDOW_NORMAL);
	imshow("Canny", image);
	waitKey(5000); // 5sec

	return 0;
}
