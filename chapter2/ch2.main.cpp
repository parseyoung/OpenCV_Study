// ������ �ٷ�� // 

#include <opencv2/core.hpp>
#include<opencv2/video.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

// cout : ǥ�� ��� ��Ʈ��, �Ϲ����� ���, ���۸� O
// cerr : ǥ�� ���� ��� ��Ʈ��, ���ۿ� ���� �޼��� ��� ����, ���� ������� X

// �ּ� ���� �� video save code

using namespace cv;
using namespace std;

int main()
{
	Mat frame;

	//VideoCapture cap(0);
	VideoCapture cap("output.mp4");

	if (!cap.isOpened())
	{
		cerr << "ī�޶� �� �� �����ϴ�." << endl;
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
		cerr << "������ ������ ���� �ʱ�ȭ�� ����" << endl;
		return -1;
	}*/
	while (1)
	{
		cap.read(frame);
		if (frame.empty())
		{
			cerr << "ĸ�� ����" << endl;
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