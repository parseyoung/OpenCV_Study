// Pixel 0~255(검~회~흰) 까지의 값을 가짐 
// color image : 3chanel. gray image : 1chanel
// image pixel 접근 방법//

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat img_color = imread("image.jpg", IMREAD_COLOR);

	if (img_color.empty())
	{
		cerr << "image not open" << endl;
		return -1;
	}

	resize(img_color, img_color, Size(), 0.5, 0.5);
	int height = img_color.rows;
	int width = img_color.cols;

	Mat img_grayscale(height, width, CV_8UC1);


	for (int y = 0; y < height; y++)
	{
		uchar* pointer_input = img_color.ptr<uchar>(y);
		uchar* pointer_output = img_grayscale.ptr<uchar>(y);

		for (int x = 0; x < width; x++)
		{
			uchar b = pointer_input[x * 3 + 0];
			uchar g = pointer_input[x * 3 + 1];
			uchar r = pointer_input[x * 3 + 2];

			pointer_output[x] = (r + g + b) / 3.0;
		}
	}
	imshow("color", img_color);
	imshow("gray", img_grayscale);

	waitKey(0);

	return 0;
}