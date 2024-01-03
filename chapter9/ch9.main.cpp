// OpenCV Image Pixel //
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;


bool mouse_is_pressing = false;
int start_x, start_y, end_x, end_y;
int step = 0;
Mat img_color;


void swap(int* v1, int* v2) 
{
	int temp = *v1;
	*v1 = *v2;
	*v2 = temp;
}


void mouse_callback(int event, int x, int y, int flags, void* userdata)
{
	Mat img_result = img_color.clone();


	if (event == EVENT_LBUTTONDOWN) 
	{
		step = 1;
		mouse_is_pressing = true;
		start_x = x;
		start_y = y;
	}
	else if (event == EVENT_MOUSEMOVE) 
	{

		if (mouse_is_pressing) 
		{
			end_x = x;
			end_y = y;
			step = 2;
		}

	}
	else if (event == EVENT_LBUTTONUP) 
	{
		mouse_is_pressing = false;
		end_x = x;
		end_y = y;
		step = 3;
	}
}

int main()
{

	//ºñµð¿À Ä¸ÃÄ ÃÊ±âÈ­
	VideoCapture cap(0);
	if (!cap.isOpened()) 
	{
		cerr << "camera not open error .\n";
		return -1;
	}

	namedWindow("Color", 1);
	setMouseCallback("Color", mouse_callback);


	while (1)
	{

		cap.read(img_color);
		if (img_color.empty()) 
		{
			cerr << "empty video error.\n";
			break;
		}

		switch (step)
		{

		case 1:
			circle(img_color, Point(start_x, start_y), 10, Scalar(0, 255, 0), -1);
			break;

		case 2:
			rectangle(img_color, Point(start_x, start_y), Point(end_x, end_y), Scalar(0, 255, 0), 3);
			break;

		case 3:
			if (start_x > end_x) 
			{
				swap(&start_x, &end_x);
				swap(&start_y, &end_y);
			}

			Mat ROI(img_color, Rect(start_x, start_y, end_x - start_x, end_y - start_y));
			cvtColor(ROI, ROI, COLOR_BGR2GRAY);
			Canny(ROI, ROI, 150, 50);
			cvtColor(ROI, ROI, COLOR_GRAY2BGR);

			ROI.copyTo(img_color(Rect(start_x, start_y, end_x - start_x, end_y - start_y)));
			break;

		}
		imshow("Color", img_color);

		if (waitKey(25) >= 0)
			break;
	}
	destroyAllWindows();

	return 0;
}
