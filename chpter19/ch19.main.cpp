///////////////  car number-palte detected  //////////////////////

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>
#include <filesystem>

using namespace cv;
using namespace std;

// webcam
int main() {

	VideoCapture cap(0);

	// 설정하려는 해상도 값 (예: 1280x720)
	int desiredWidth = 640;
	int desiredHeight = 367;

	// 카메라의 해상도 설정
	cap.set(CAP_PROP_FRAME_WIDTH, desiredWidth);
	cap.set(CAP_PROP_FRAME_HEIGHT, desiredHeight);

	if (!cap.isOpened()) {
		cerr << "Error opening video file" << endl;
		return -1;
	}

	Mat img;

	CascadeClassifier plateCascade;
	plateCascade.load("C:/Users/samsung/openCV/opencv/sources/data/haarcascades/haarcascade_russian_plate_number.xml");

	if (plateCascade.empty()) { cout << "XML file not loaded" << endl; }

	vector<Rect> plates;

	while (true)
	{
		cap.read(img);
		//detectMultiScale(InputArray image, vector<Rect>& objects, scaleFactor, minNeighbors, ...) 
		plateCascade.detectMultiScale(img, plates, 1.1, 10);
	

		for (int i = 0; i < plates.size(); i++)
		{
			Mat imgCrop = img(plates[i]);
			//imshow(to_string(i), imgCrop);
			imwrite("plate/" + to_string(i) + ".png", imgCrop);
			// 0.png, 1.png, 2.png ... 
			rectangle(img, plates[i].tl(), plates[i].br(), Scalar(255, 0, 255), 3);
		}

		imshow("image", img);


		if (waitKey(1) == 27)
			break;
	}

	return 0;

}