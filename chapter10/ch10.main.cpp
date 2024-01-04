#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
using namespace cv;
using namespace std;

// Contour 영역 내에 텍스트 , vector<Point> : 2D공간에서 여러 점의 좌표 저장 가능 동적배열
void setLabel(Mat& image, string str, vector<Point> contour)
{
	int fontface = FONT_HERSHEY_SIMPLEX;
	double scale = 0.5;
	int thickness = 1;
	int baseline = 0;

	Size text = getTextSize(str, fontface, scale, thickness, &baseline);
	Rect r = boundingRect(contour);

	Point pt(r.x + ((r.width - text.width) / 2), r.y + ((r.height + text.height) / 2));
	rectangle(image, pt + Point(0, baseline), pt + Point(text.width, -text.height), CV_RGB(200, 200, 200), FILLED);
	putText(image, str, pt, fontface, scale, CV_RGB(0, 0, 0), thickness, 8);
}

int main(int, char**)
{
	Mat img_input, img_result, img_gray;

	img_input = imread("test.jpg", IMREAD_COLOR);
	if (img_input.empty())
	{
		cerr << "Could not open or file the image" << endl;
		return -1;
	}

	cvtColor(img_input, img_gray, COLOR_BGR2GRAY);

	// 이진화 이미지로 변환
	Mat binary_image;
	// threshold (입력, 출력, 임계값, 임계값 이상 시 적용 값, flag)
	// THRESH_BINARY_INV : 임계값 넘으면 0, 그렇지 않으면 최대 밝기 값
	// THRESH_OTSU : 최적화된 이진화 임계값 자동 선택, 세번째 임계값 인자 무시
	threshold(img_gray, img_gray, 0, 255, THRESH_BINARY_INV | THRESH_OTSU);

	// contour 찾는다
	vector<vector<Point>> contours;
	// findContours() : 이미지의 외곽선 찾는 func
	// findContours(입력, 저장벡터, 외곽선 찾는 방법 flag, 외곽선 표현 방법 flag)
	// RETR_LIST : 외곽선을 찾아 리스트형태로 반환
	// CHAIN_APPROX_SIMPLE : 외곽선을 효과적으로 압축하여 표현
	findContours(img_gray, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);

	// contour 근사화
	vector<Point2f> approx;
	// Point2f : 부동 소수점 형태
	img_result = img_input.clone();

	for (size_t i = 0; i < contours.size(); i++)
		// size_t : 배열의 인덱스나 요소 개수를 나타내는데 사용하는 부호 없는 정수형
	{
		// approxPolyDP() : 다각형 근사화 func
		approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true) * 0.02, true);
		if (fabs(contourArea (Mat(approx))) > 100)
		{
			int size = approx.size();

			// contour 근사화한 직선 그리기
			if (size % 2 == 0)
			{
				line(img_result, approx[0], approx[approx.size() - 1], Scalar(0, 255, 0), 3);

				for (int k = 0; k < size - 1; k++)
				{
					line(img_result, approx[k], approx[k + 1], Scalar(0, 255, 0), 3);
				}

				for (int k = 0; k < size; k++)
				{
					circle(img_result, approx[k], 3, Scalar(0, 0, 255));
				}
			}

			else
			{
				line(img_result, approx[0], approx[approx.size() - 1], Scalar(0, 255, 0), 3);

				for (int k = 0; k < size - 1; k++)
				{
					line(img_result, approx[k], approx[k + 1], Scalar(0, 255, 0), 3);
				}

				for (int k = 0; k < size; k++)
				{
					circle(img_result, approx[k], 3, Scalar(0, 0, 255));
				}
			}
			if (isContourConvex(Mat(approx)))
			{
				if (size == 3)
					setLabel(img_result, "triangle", contours[i]);
				else if (size == 4 && isContourConvex(Mat(approx)))
					setLabel(img_result, "rectangle", contours[i]);
				else if (size == 5 && isContourConvex(Mat(approx)))
					setLabel(img_result, "pentagon", contours[i]);
				else if (size == 6 && isContourConvex(Mat(approx)))
					setLabel(img_result, "hexagon", contours[i]);
				else if (size == 10 && isContourConvex(Mat(approx)))
					setLabel(img_result, "decangon", contours[i]);
				else if (size >= 5 && size <= 8)
					{
						RotatedRect ellipse = fitEllipse(approx);
						double ratio = min(ellipse.size.width, ellipse.size.height) / max(ellipse.size.width, ellipse.size.height);
						if (ratio >= 0.8 && ratio <= 1.0)
							setLabel(img_result, "circle", contours[i]);
					}
				else
					setLabel(img_result, to_string(approx.size()), contours[i]);
			}
			else
			{
				setLabel(img_result, "Non-convex", contours[i]);

			}
		}

	}

	imshow("input", img_input);
	imshow("result", img_result);

	waitKey(0);

	return 0;
}


