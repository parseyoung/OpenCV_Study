// 동영상 다루기 // 

#include <opencv2/core.hpp>
#include<opencv2/video.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

// cout : 표준 출력 스트림, 일반적인 출력, 버퍼링 O
// cerr : 표준 오류 출력 스트림, 버퍼에 남은 메세지 출력 가능, 버퍼 비워지지 X

// 주석 해제 시 video save code

using namespace cv;
using namespace std;

int main()
{
	Mat frame;

	//VideoCapture cap(0);
	VideoCapture cap("output.mp4");

	if (!cap.isOpened())
	{
		cerr << "카메라를 열 수 없습니다." << endl;
		return -1;
	}

	int fps = 10;
	/*int width = cap.get(CAP_PROP_FRAME_WIDTH);
	int height = cap.get(CAP_PROP_FRAME_HEIGHT);
	int fourcc = VideoWriter::fourcc('X', '2', '6', '4');

	VideoWriter outputVideo;
	outputVideo.open("output.mp4", fourcc, fps, Size(width, height), true);
	if (!outputVideo.isOpened())
	{
		cerr << "동영상 저장을 위한 초기화중 에러" << endl;
		return -1;
	}*/
	while (1)
	{
		cap.read(frame);
		if (frame.empty())
		{
			cerr << "캡쳐 실패" << endl;
			//return -1;
			break;
		}

		Mat gray_frame;

		cvtColor(frame, gray_frame, COLOR_BGR2GRAY);

		imshow("Live", gray_frame);

		//outputVideo.write(gray_frame);

		int wait = int(1.0 / fps * 1000);
		if (waitKey(wait) >= 0)
			break;
		//waitKey(0);
	}

	return 0;
}