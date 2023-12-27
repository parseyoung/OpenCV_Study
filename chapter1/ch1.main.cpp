#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/types.hpp"

int main() {
	cv::namedWindow("test");
	cv::Mat mat = cv::Mat::zeros(300, 300, CV_8U);
	cv::imshow("test", mat);
	cv::waitKey(0);

	cv::destroyAllWindows();

	return 0;
}