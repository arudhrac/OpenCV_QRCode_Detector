#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;

void display(Mat& im, Mat& bbox)
{
	int n = bbox.rows;
	for (int i = 0; i < n; i++)
	{
		line(im, Point2i(bbox.at<float>(i, 0), bbox.at<float>(i, 1)), Point2i(bbox.at<float>((i + 1) % n, 0), bbox.at<float>((i + 1) % n, 1)), Scalar(255, 0, 0), 3);
	}
	imshow("Result", im);
}

int main(int argv, char* argc[]) {

	Mat img = imread("ac.png");

	QRCodeDetector qrDecoder = QRCodeDetector::QRCodeDetector();

	Mat bbox, rectifiedImage;

	string data = qrDecoder.detectAndDecode(img, bbox, rectifiedImage);

	if (data.length() > 0)
	{
		cout << "Decoded Data : " << data << endl;

		display(img, bbox);
		rectifiedImage.convertTo(rectifiedImage, CV_8UC3);
		imshow("Rectified QRCode", rectifiedImage);

		waitKey(0);
	}
	else{
		cout << "QR Code not detected" << endl;
	}


	return 0;


}