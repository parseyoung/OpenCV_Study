// Color Dection  for trackbar//
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
using namespace cv;
using namespace std;

// color detedtion //
Mat imgHSV, mask;
// trackbar를 통해 찾은 orange color 최적 값
//int hmin = 0, smin = 141, vmin = 115;
//int hmax = 179, smax = 241, vmax = 255;

// for 여러가지 도형 image.jpg
// trackbar를 통해 찾은 green color 최적 값 
int hmin = 60, smin = 0, vmin = 0;
int hmax = 80, smax = 255, vmax = 216;


void main()
{
	//string path = "lambo.jpg";
	string path = "image.jpg";

	Mat img = imread(path);
	cvtColor(img, imgHSV, COLOR_BGR2HSV);

	namedWindow("Trackbar", (640, 200));
	createTrackbar("Hue Min", "Trackbar", &hmin, 179);
	createTrackbar("Hue Max", "Trackbar", &hmax, 179);
	createTrackbar("Sat Min", "Trackbar", &smin, 255);
	createTrackbar("Sat Max", "Trackbar", &smax, 255);
	createTrackbar("Val Min", "Trackbar", &vmin, 255);
	createTrackbar("Val Max", "Trackbar", &vmax, 255);

	while (true)
	{
		Scalar lower(hmin, smin, vmin);
		Scalar upper(hmax, smax, vmax);

		inRange(imgHSV, lower, upper, mask);


		imshow("image", img);
		imshow("image HSV", imgHSV);
		imshow("image mask", mask);
		waitKey(1) == 27; // ESC
	}

	
}