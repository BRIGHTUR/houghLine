#include<iostream>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
	Mat srcMat = imread("test.png");
	Mat cannyMat;
	Mat dstMat;
	cvtColor(srcMat, dstMat, CV_BGR2GRAY);
	Canny(dstMat, cannyMat, 100, 170, 3);
	vector<cv::Vec2f> lines;
	HoughLines(cannyMat, lines, 1, CV_PI / 180, 100);
	std::vector<cv::Vec2f>::iterator it = lines.begin();
	for (; it != lines.end(); ++it) {
		float rho = (*it)[0], theta = (*it)[1];
		Point pt1, pt2;
		double a = cos(theta);
		double b = sin(theta);
		double x0 = a*rho;
		double y0 = b*rho;
		pt1.x = cv::saturate_cast<int>(x0 + 1000 * (-b));
		pt1.y = cv::saturate_cast<int>(y0 + 1000 * (a));
		pt2.x = cv::saturate_cast<int>(x0 - 1000 * (-b));
		pt2.y = cv::saturate_cast<int>(y0 - 1000 * (a));
		line(srcMat, pt1, pt2, cv::Scalar(255, 255, 0), 1, CV_AA);
	}
	imshow("dst", cannyMat);
	imshow("src", srcMat);
	waitKey(0);
}