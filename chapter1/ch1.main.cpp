// opencv�� ��⺰�� ����� �������� �־� �������� ����� include ��
// #include <opencv2/opencv.hpp> : �ϳ��� include �ϴ� ����� ����
// opencv�� c++�� �浹�� ���� ���̺귯������ ���� usingnamespace ��� ����

// �̹��� �ٷ�� // 

#include <opencv2/core.hpp> // opencv �⺻ �ڷᱸ�� �� �Լ�
#include <opencv2/imgcodecs.hpp> // image read & save
#include <opencv2/highgui.hpp> // interface
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp> // canny function

// c++ headers
#include <iostream> 

using namespace std;
using namespace cv;

int main()
{
	Mat image;
	image = imread("house.jpg", IMREAD_GRAYSCALE);
	if (image.empty())
	{
		cout << "Could not open or find the i";
		return -1;
	}

	// second argument 
	// WINDOW_NORMAL : �̹��� ũ�� �����Ӱ� ���� ����
	// WND_PROP_FULLSCREEN : ��ü ȭ��
	namedWindow("Original", WND_PROP_FULLSCREEN);
	setWindowProperty("Original", WND_PROP_FULLSCREEN, WINDOW_FULLSCREEN);
	imshow("Original", image);
	waitKey(0);

	Canny(image, image, 50, 150);
	namedWindow("Canny", WINDOW_NORMAL);
	imshow("Canny", image);
	waitKey(5000); // 5sec

	return 0;
}
