#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/types.hpp"

//int main() {
//	cv::namedWindow("test");
//	cv::Mat mat = cv::Mat::zeros(300, 300, CV_8U);
//	cv::imshow("test", mat);
//	cv::waitKey(0);
//
//	cv::destroyAllWindows();
//
//	return 0;
//}

#include <iostream> 

using namespace std;
using namespace cv;

int main()
{
	Mat image;
	image = imread("house.jpg", IMREAD_COLOR);
	if (image.empty())
	{
		cout << "Could not open or find the i";
		return -1;
	}

	namedWindow("Original", WINDOW_AUTOSIZE);
	imshow("Original", image);

	waitKey(0);

	return 0;
}
