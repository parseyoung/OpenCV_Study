//  관심영역 Region of Interset(ROI) 사용 법 //

#include <opencv2/opencv.hpp>
using namespace cv;

bool mouse_is_pressing = false;
int start_x = -1, start_y = -1; // 마우스 클릭 X 상태 
Mat img_color;

void mouse_callback(int event, int x, int y, int flags, void* userdata)
{
	Mat img_result = img_color.clone(); //img_color copy하여 img_result 생성

	if (event == EVENT_LBUTTONDOWN)
	{
		mouse_is_pressing = true;
		start_x = x;
		start_y = y;

		circle(img_result, Point(x, y), 10, Scalar(0, 255, 0), -1);
		// (대상이미지, 원의 중심 좌표, 반지름, 원 색상(초록), 원 내부 채워짐)
		imshow("img_color", img_result);
	}
	else if (event == EVENT_MOUSEMOVE)
	{
		if (mouse_is_pressing)
		{
			rectangle(img_result, Point(start_x, start_y), Point(x, y), Scalar(0, 255, 0), 3);

			imshow("img_color", img_result);
		}
	}
	else if (event == EVENT_LBUTTONUP)
	{
		mouse_is_pressing = false;
		Mat img_psy(img_color, Rect(start_x, start_y, x - start_x, y - start_y));
		cvtColor(img_psy, img_psy, COLOR_BGR2GRAY);
		cvtColor(img_psy, img_psy, COLOR_GRAY2BGR);

		img_psy.copyTo(img_result(Rect(start_x, start_y, x - start_x, y - start_y)));
		imshow("img_color", img_result);
		imshow("img_psy", img_psy);
	}

}
int main()
{
	img_color = imread("psy.jpg", IMREAD_COLOR);

	Size newSize(480, 640);
	resize(img_color, img_color, newSize);

	imshow("img_color", img_color);
	setMouseCallback("img_color", mouse_callback);

	waitKey(0);
	destroyAllWindows();
}
