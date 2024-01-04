#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
using namespace cv;
using namespace std;

// Contour ���� ���� �ؽ�Ʈ , vector<Point> : 2D�������� ���� ���� ��ǥ ���� ���� �����迭
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

	// ����ȭ �̹����� ��ȯ
	Mat binary_image;
	// threshold (�Է�, ���, �Ӱ谪, �Ӱ谪 �̻� �� ���� ��, flag)
	// THRESH_BINARY_INV : �Ӱ谪 ������ 0, �׷��� ������ �ִ� ��� ��
	// THRESH_OTSU : ����ȭ�� ����ȭ �Ӱ谪 �ڵ� ����, ����° �Ӱ谪 ���� ����
	threshold(img_gray, img_gray, 0, 255, THRESH_BINARY_INV | THRESH_OTSU);

	// contour ã�´�
	vector<vector<Point>> contours;
	// findContours() : �̹����� �ܰ��� ã�� func
	// findContours(�Է�, ���庤��, �ܰ��� ã�� ��� flag, �ܰ��� ǥ�� ��� flag)
	// RETR_LIST : �ܰ����� ã�� ����Ʈ���·� ��ȯ
	// CHAIN_APPROX_SIMPLE : �ܰ����� ȿ�������� �����Ͽ� ǥ��
	findContours(img_gray, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);

	// contour �ٻ�ȭ
	vector<Point2f> approx;
	// Point2f : �ε� �Ҽ��� ����
	img_result = img_input.clone();

	for (size_t i = 0; i < contours.size(); i++)
		// size_t : �迭�� �ε����� ��� ������ ��Ÿ���µ� ����ϴ� ��ȣ ���� ������
	{
		// approxPolyDP() : �ٰ��� �ٻ�ȭ func
		approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true) * 0.02, true);
		if (fabs(contourArea (Mat(approx))) > 100)
		{
			int size = approx.size();

			// contour �ٻ�ȭ�� ���� �׸���
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


