// face detection //
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>
using namespace std;
using namespace cv;

int main()
{
    string path = "psy.jpg";
    Mat img = imread(path);

    CascadeClassifier faceCaseade;

    //faceCaseade.load("C:/Users/samsung/openCV/opencv/sources/data/haarcascades_cuda/haarcascade_eye.xml");
    faceCaseade.load("C:/Users/samsung/openCV/opencv/sources/data/haarcascades_cuda/haarcascade_frontalface_default.xml");

    if (faceCaseade.empty()) 
    {
        cerr << "XML file not load" << endl;
        return -1;  
    }

    vector<Rect> faces;
    faceCaseade.detectMultiScale(img, faces, 1.1, 10);

    for (int i = 0; i < faces.size(); i++)
    {
        rectangle(img, faces[i].tl(), faces[i].br(), Scalar(255, 0, 255), 3);
    }

    imshow("Detected Faces", img);
    waitKey(0); 

    return 0;
}
