// shapes & contour detector //

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Mat imgGray, imgBlur, imgCanny, imgDil, imgErode;

void getContours(Mat imgDil, Mat img)
{
	vector <vector<Point>> contours;
	vector<Vec4i> hierarchy; // four int vec

	findContours(imgDil, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);
	//drawContours(img, contours, -1, Scalar(255, 0, 255), 2);  // -1 : all drawing
	
	for (int i = 0; i < contours.size(); i++)
	{
		int area = contourArea(contours[i]);
		cout << area << endl; // noise size check

		vector<vector<Point>> conPoly(contours.size());
		vector<Rect> boundRect(contours.size());
		string objectType;

		if (area > 1000)
		{
			// true flag : close
			float peri = arcLength(contours[i], true);
			approxPolyDP(contours[i], conPoly[i], 0.019 * peri, true);
			//drawContours(img, contours, i, Scalar(255, 0, 255), 2);  // -1 : all drawing
			cout << conPoly[i].size() << endl;
			//boundRect[i] = boundingRect(conPoly[i]);
			//rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 3);

			int objCor = (int)conPoly[i].size();

			if (objCor == 3) { objectType = "Tri"; }
			else if (objCor == 4)
			{
				float aspRatio = (float)boundRect[i].width / (float)boundRect[i].height;
				cout << aspRatio << endl;
				if (aspRatio > 0.95 && aspRatio < 1.05) { objectType = "squre"; }
				else { objectType = "Rect"; }
			}
			else if (objCor > 4) { objectType = "Circle"; }
			drawContours(img, contours, i, Scalar(255, 0, 255), 3);  // -1 : all drawing
			boundRect[i] = boundingRect(conPoly[i]);
			rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 2);
			putText(img, objectType, { boundRect[i].x, boundRect[i].y - 5 }, FONT_HERSHEY_PLAIN, 1, Scalar(0, 69, 255), 2);
		}

	}



}

// images
void main()
{
	string path = "image.jpg";
	Mat img = imread(path);
	//Size imgsize(500, 500);
	//resize(img, img, imgsize);

	// preprocessing : 이미지 전처리 
	cvtColor(img, imgGray, COLOR_BGR2GRAY);
	GaussianBlur(imgGray, imgBlur, Size(3, 3), 3, 0);
	Canny(imgBlur, imgCanny, 20, 75);
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	dilate(imgCanny, imgDil, kernel);

	getContours(imgDil, img);

	imshow("image", img);
	//imshow("image Gray", imgGray);
	//imshow("image Blur", imgBlur);
	//imshow("image Canny", imgCanny);
	//imshow("image Dil", imgDil);

	waitKey(0);
}