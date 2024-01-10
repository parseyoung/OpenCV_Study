// Document Scanner for image, mp4, waecam //

#include <opencv2/core.hpp>
#include<opencv2/video.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Mat imgOriginal, imgGray, imgBlur, imgCanny, imgThre, imgDil, imgErode, imgWrap, imgCrop;
vector<Point> initialPoints, docPoints;

float w = 420, h = 596;

Mat preProcessing(Mat img)
{
	cvtColor(img, imgGray, COLOR_BGR2GRAY);
	GaussianBlur(imgGray, imgBlur, Size(5, 5), 3, 0);
	Canny(imgBlur, imgCanny, 25, 75);

	Mat kernel = getStructuringElement(MORPH_RECT, Size(2, 2));
	dilate(imgCanny, imgDil, kernel); // 팽창
	erode(imgDil, imgErode, kernel);
	return imgDil;
}

vector<Point> getContours(Mat imgDil)
{
	vector <vector<Point>> contours;
	vector<Vec4i> hierarchy; // four int vec

	findContours(imgDil, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);
	//drawContours(img, contours, -1, Scalar(255, 0, 255), 2);  // -1 : all drawing
	vector<vector<Point>> conPoly(contours.size());
	vector<Rect> boundRect(contours.size());

	vector<Point> biggest;
	int maxArea = 0;

	for (int i = 0; i < contours.size(); i++)
	{
		int area = contourArea(contours[i]);
		//cout << area << endl; // noise size check
		string objectType;

		if (area > 1000)
		{
			float peri = arcLength(contours[i], true);
			approxPolyDP(contours[i], conPoly[i], 0.019 * peri, true);
			
			if (area > maxArea && conPoly[i].size() >= 4 )
			{
				//drawContours(imgOriginal, contours, i, Scalar(255, 0, 255), 5);  // -1 : all drawing
				biggest = { conPoly[i][0], conPoly[i][1], conPoly[i][2], conPoly[i][3] };
				maxArea = area;
			}
			else
			{
				cout << conPoly[i] << "not 4" << endl;
			}

			//drawContours(imgOriginal, contours, i, Scalar(255, 0, 255), 3);  // -1 : all drawing
			//rectangle(imgOriginal, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 2);
		}

	}

	return biggest;

}

void drawPoints(vector<Point> points, Scalar color)
{
	for (int i = 0; i < points.size(); i++)
	{
		circle(imgOriginal, points[i], 10, color, FILLED);
		putText(imgOriginal, to_string(i), points[i], FONT_HERSHEY_PLAIN, 4, color, 4);
	}
}

vector<Point> reorder(vector<Point> points)
{
	vector<Point> newPoints;
	vector<int> sumPoints, subPoints;
	
	for (int i = 0; i < points.size(); i++)
	{
		sumPoints.push_back(points[i].x + points[i].y);
		subPoints.push_back(points[i].x - points[i].y);
	}
	newPoints.push_back(points[min_element(sumPoints.begin(), sumPoints.end()) - sumPoints.begin()]);
	newPoints.push_back(points[max_element(subPoints.begin(), subPoints.end()) - subPoints.begin()]);
	newPoints.push_back(points[min_element(subPoints.begin(), subPoints.end()) - subPoints.begin()]);
	newPoints.push_back(points[max_element(sumPoints.begin(), sumPoints.end()) - sumPoints.begin()]);

	return newPoints;
}

Mat getWrap(Mat img, vector<Point> points, float w, float h)
{
	if (points.size() == 4)
	{
		Point2f src[4] = { points[0], points[1], points[2], points[3] };
		Point2f dst[4] = { {0.0f, 0.0f}, {w, 0.0f}, {0.0f, h}, {w, h} };
		Mat matrix = getPerspectiveTransform(src, dst);
		warpPerspective(img, imgWrap, matrix, Point(w, h));

		return imgWrap;
	}
	else
	{
		// 유효한 꼭지점이 아닌 경우, 처리할 내용 추가
		cout << "유효한 4개의 꼭지점이 아닙니다." << endl;
		// dosomething()
		return img;  // 또는 빈 행렬을 반환하거나 다른 방식으로 처리할 수 있습니다.
	}
}


int main()
{
	//string path = "paper.jpg";

	/*string videopath = "paper.mp4";
	VideoCapture cap(videopath);*/

	VideoCapture cap(0);


	if (!cap.isOpened())
	{
		cerr << "Error opening video file" << endl;
		return -1;
	}

	while (true)
	{
		Mat frame;
		cap >> frame;
		imgOriginal = frame.clone();
		/*if (frame.empty())
		{
			cerr << "End of Video" << endl;
			break;
		}*/ // for mp4

		//imgOriginal = imread(path);
		//resize(imgOriginal, imgOriginal, Size(), 0.5, 0.5);

		//preprocessing - Step 1
		//Mat imaThre = preProcessing(imgOriginal);
		imgThre = preProcessing(frame);

		// get contours - Biggest - Step 2
		initialPoints = getContours(imgThre);
		//drawPoints(initialPoints, Scalar(0, 0, 255));
		docPoints = reorder(initialPoints);
		//drawPoints(docPoints, Scalar(0, 255, 0));

		// wrap - Step 3
		imgWrap = getWrap(imgOriginal, docPoints, w, h);

		//crop - Step 4
		int cropVal = 5;

		Rect roi(cropVal, cropVal, w - (2 * cropVal), h - (2 * cropVal));
		imgCrop = imgWrap(roi);

	/*	imshow("image", imgOriginal);
		imshow("image Dilation", imgThre);
		imshow("image Wrap", imgWrap);
		imshow("image Crop", imgCrop);*/

		imshow("Vedeo Frame", frame);
		imshow("image Crop", imgCrop);

		if (waitKey(1) == 27) // ESC
			break;
	}

	//destroyAllWindows();
	cap.release();
	return 0;
}
