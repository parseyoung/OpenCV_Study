// C++ : ������ �����Ͽ� argument�� �Լ��� �Ѱ��� �� ��� �̹��� ����
// Python : �Լ��� return ������ ��� �̹��� ����

// Labeling (���̺�, �󺧸�) //

#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;


int main()
{
	// 0
	Mat image = imread("test.jpg", IMREAD_COLOR);
	Size newSize(640, 480);
	resize(image, image, newSize);
	imshow("result", image);
	waitKey(0);

	Mat blurred;
	// GaussianBlur()�� Ŀ�� ũ��� Ȧ���� ���� ���� ���� ��.
	Size blurSize(7, 7);
	GaussianBlur(image, blurred, blurSize, 0);
	
	Mat gray;
	cvtColor(blurred, gray, COLOR_BGR2GRAY);
	imshow("result", gray);
	waitKey(0);

	Mat edge;
	Canny(gray, edge, 50, 150);
	imshow("result", edge);
	waitKey(0);

	// 1
	bitwise_not(edge, edge);
	imshow("result", edge);
	waitKey(0);

	vector<vector<Point>> contours;
	findContours(edge.clone(), contours, RETR_LIST, CHAIN_APPROX_SIMPLE);
	drawContours(edge, contours, -1, Scalar(0, 0, 0), 1);
	imshow("result", edge);
	waitKey(0);

	//2
	Mat labels, stats, centroids;
	int nlabels = connectedComponentsWithStats(edge, labels, stats, centroids);

	for (int i = 0; i < nlabels; i++)
	{
		if (i < 2) continue;
		int area = stats.at<int>(i, CC_STAT_AREA);
		int center_x = centroids.at<double>(i, 0); // 0: x��ǥ
		int center_y = centroids.at<double>(i, 1); // 1 : y��ǥ
		int left = stats.at<int>(i, CC_STAT_LEFT);
		int top = stats.at<int>(i, CC_STAT_TOP);
		int width = stats.at<int>(i, CC_STAT_WIDTH);
		int height = stats.at<int>(i, CC_STAT_HEIGHT);

		if (area > 50)
		{
			rectangle(image, Point(left, top),
				Point(left + width, top + height),
				Scalar(0, 0, 255), 1);
			circle(image, Point(center_x, center_y), 5, (255, 0, 0), 1);
			putText(image, to_string(i), Point(left + 20, top + 20),
				FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 0, 0), 2);
		}
	}
	imshow("result", image);
	waitKey(0);
}
