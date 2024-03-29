// openCV 사용해서 실시간 도형 검출하기 - shape detection for webcam //
// ch10 차이점 
// 이진화 방법을 adaptiveThreshold 함수로 변경, GaussianBlur 함수 추가
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
using namespace cv;
using namespace std;


void setLabel(Mat& image, string str, vector<Point> contour)
{
	int fontface = FONT_HERSHEY_SIMPLEX;
	double scale = 0.5;
	int thinckness = 1;
	int baseline = 0;

	Size text = getTextSize(str, fontface, scale, thinckness, &baseline);
	Rect r = boundingRect(contour);
	Point pt(r.x + ((r.width - text.width) / 2), r.y + ((r.height + text.height) / 2));
	rectangle(image, pt + Point(0, baseline), pt + Point(text.width, -text.height), CV_RGB(200, 200, 200), FILLED);
	putText(image, str, pt, fontface, scale, CV_RGB(0, 0, 0), thinckness, 8);
}

int main(int, char**)
{
	Mat img_input, img_result, img_gray;

	VideoCapture cap;

	int deviceID = 0;
	int apiID = CAP_ANY;

	cap.open(deviceID + apiID);

	if (!cap.isOpened())
	{
		cerr << "ERROR! unable to open camera\n";
		return -1;
	}

	for (;;)
	{
		cap.read(img_input);
		if (img_input.empty())
		{
			cerr << "ERROR! blank frame grabbed\n";
			break;
		}

		Mat img_temp;
		Size blursize(5, 5);
		cvtColor(img_input, img_temp, COLOR_BGR2GRAY);
		GaussianBlur(img_temp, img_temp, blursize, 0, 0);
	
		// binary image
		// adaptiveThreshold() : 적응형 이진화 수행 func
		// adaptiveThreshold(src, dst, maxValue, adaptiveMethod, thresholdType, blockSize, C);

		adaptiveThreshold(img_temp, img_gray, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY_INV, 201, 7);

		// contour serch
		vector<vector<Point>> contours;
		findContours(img_gray, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);

		// contour 근사화
		vector<Point2f> approx;
		img_result = img_input.clone();

		for (size_t i = 0; i < contours.size(); i++)
		{
			approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*0.02, true);
			// 특정 범위를 가진 면적의 도형만 고려 
			if (fabs(contourArea(Mat(approx))) > 1000 && fabs(contourArea(Mat(approx))) < 10000)
			{
				int size = approx.size();
				const char *name[] = { "Non-convex", "Non-convex", "Non-convex", "triangle", 
					"quadrangle", "pentagon", "hexagon", "heptagon", "octagon", "nonagon", "decagon" };
				
				switch (size){

				
					case 3:
					case 4:
					case 5:
					case 6:
					case 10:
						if (isContourConvex(Mat(approx)))
						{
							if (size % 2 == 0)
							{
								line(img_result, approx[0], approx[approx.size() - 1], Scalar(0, 255, 0), 3);

								for (int k = 0; k < size - 1; k++)
									line(img_result, approx[k], approx[k + 1], Scalar(0, 255, 0), 3);

								for (int k = 0; k < size; k++)
									circle(img_result, approx[k], 3, Scalar(0, 0, 255));
							}
							else
							{
								line(img_result, approx[0], approx[approx.size() - 1], Scalar(0, 255, 0), 3);

								for (int k = 0; k < size - 1; k++)
									line(img_result, approx[k], approx[k + 1], Scalar(0, 255, 0), 3);

								for (int k = 0; k < size; k++)
									circle(img_result, approx[k], 3, Scalar(0, 0, 255));
							}

							// 검출된 도형에 라벨 출력
							setLabel(img_result, name[size], contours[i]);
						}
						break;
					
				default:
					break;

				}
			}
		}

		imshow("result", img_result);
		imshow("binary", img_gray);

		if (waitKey(5) == 27) // waiting for ESC
			break;
	}


	return 0;
}