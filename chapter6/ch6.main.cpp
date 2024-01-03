// template matching //

#include <opencv2/opencv.hpp>
#include <iostream>
#include <opencv2/core.hpp>
using namespace std;
using namespace cv;

typedef struct _PointInfo
{
	int x;
	int y;
	int sad;
}PointInfo;

int main()
{
	Mat img_color = imread("image.jpg", IMREAD_COLOR);
	Mat img_original;
	cvtColor(img_color, img_original, COLOR_BGR2GRAY);

	Mat img_template = imread("template.jpg", IMREAD_GRAYSCALE);

	int original_h = img_original.rows;
	int original_w = img_original.cols;
	int template_h = img_template.rows;
	int template_w = img_template.cols;

	int best_position_y = 0;
	int best_position_x = 0;
	int best_position_sad = 100000;

	vector<PointInfo> point;

	// ¿øº» ÀÌ¹ÌÁö ½ºÄµ
	for (int original_y = 0; original_y < original_h - template_h; original_y++)
	{
		for (int original_x = 0; original_x < original_w - template_w; original_x++)
		{
			int SAD = 0;

			// ÅÛÇÃ¸´ ÀÌ¹ÌÁö ½ºÄµ
			for (int template_y = 0; template_y < template_h; template_y++)
			{
				for (int template_x = 0; template_x < template_w; template_x++)
				{
					int original_pixel = img_original.at<uchar>(original_y + template_y, original_x + template_x);
					int template_pixel = img_template.at<uchar>(template_y, template_x);

					SAD += abs(original_pixel - template_pixel);
				}
			}

			if (best_position_sad > SAD)
			{
				best_position_sad = SAD;
				best_position_y = original_y;
				best_position_x = original_x;
			}

			PointInfo pointinfo = { original_x, original_y, SAD };
			point.push_back(pointinfo);
		}
	}

	for (int i = 0; i < point.size(); i++)
	{
		if (abs(best_position_sad - point[i].sad) < 100)
		{
			cout << abs(best_position_sad - point[i].sad) << endl;
			rectangle(img_color, Point(point[i].x, point[i].y), Point(point[i].x + template_w,
				point[i].y + template_h), Scalar(255, 0, 0), 3);
		}
	}

	imshow("result", img_color);
	waitKey(0);
}