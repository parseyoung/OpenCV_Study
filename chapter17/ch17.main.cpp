// Virtual Painter // 
// chapter ColorPicker.cpp 로 원하는 색상 값 확인 후, myColors 값 측정한다.
// 측정값의 BGR을 myColorValues에 넣어주면 웹캠을 통해 받아드린 지정 색상으로 그림 그리기 가능
#include <opencv2/core.hpp>
#include<opencv2/video.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Mat img;
vector<vector<int>> newPoints;


vector<vector<int>> myColors{ 
	{65, 62, 94, 179, 255, 255}, // red
	{6, 0, 118, 129, 38, 213} // white 
}; 

vector<Scalar> myColorValues
{
	{0, 0, 255}, // red
	{255, 255, 255} // white
};

Point getContours(Mat imgDil)
{
	vector <vector<Point>> contours;
	vector<Vec4i> hierarchy; // four int vec

	findContours(imgDil, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);
	//drawContours(img, contours, -1, Scalar(255, 0, 255), 2);  // -1 : all drawing
	vector<vector<Point>> conPoly(contours.size());
	vector<Rect> boundRect(contours.size());

	Point myPoint(0, 0);

	for (int i = 0; i < contours.size(); i++)
	{
		int area = contourArea(contours[i]);
		cout << area << endl; // noise size check
		string objectType;

		if (area > 1000)
		{
			float peri = arcLength(contours[i], true);
			approxPolyDP(contours[i], conPoly[i], 0.019 * peri, true);
			cout << conPoly[i].size() << endl;

			int objCor = (int)conPoly[i].size();
			boundRect[i] = boundingRect(conPoly[i]);
			myPoint.x = boundRect[i].x + boundRect[i].width / 2;
			myPoint.y = boundRect[i].y;

			
			drawContours(img, contours, i, Scalar(255, 0, 255), 3);  // -1 : all drawing
			rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 2);
		}

	}
	return myPoint;

}
vector<vector<int>> findColor(Mat img)
{
	Mat imgHSV;
	cvtColor(img, imgHSV, COLOR_BGR2HSV);
	
	for (int i = 0; i < myColors.size(); i++)
	{
		Scalar lower(myColors[i][0], myColors[i][1], myColors[i][2]);
		Scalar upper(myColors[i][3], myColors[i][4], myColors[i][5]);
		Mat mask;
		inRange(imgHSV, lower, upper, mask);
		Point myPoint = getContours(mask);
		if (myPoint.x != 0 & myPoint.y != 0)
		{
			newPoints.push_back({ myPoint.x , myPoint.y, i });
		}
	}
	return newPoints;
}

void drawOnCanvas(vector<vector<int>> newPoints, vector<Scalar> myColorValues)
{
	for (int i = 0; i < newPoints.size(); i++)
	{
		circle(img, Point(newPoints[i][0], newPoints[i][1]), 10, myColorValues[newPoints[i][2]], FILLED);
	}
}

void main()
{
	VideoCapture cap(0);


	if (!cap.isOpened())
	{
		cerr << "카메라를 열 수 없습니다." << endl;
	}
	while (true)
	{
		cap.read(img);
		newPoints = findColor(img);
		drawOnCanvas(newPoints, myColorValues);
		imshow("image", img);
		waitKey(1);
	}
}

	