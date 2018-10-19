#include <opencv2\opencv.hpp>
#include <opencv2\cvconfig.h>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include "Function.h"

using namespace cv;
using namespace std;

double RightTriangle(int A, int C) {
	A = A * A;
	C = C * C;
	double Sub = C - A;
	double Result = sqrt(Sub);
	return Result;
}

String TwoDecimalString(double Input) {
	stringstream stream;
	stream << fixed << setprecision(2) << Input;
	string Output = stream.str();
	return Output;
}


Mat PutTextOnMe(Mat SRC, String Text, int Color, int x, int y) {

	Scalar SelectedColor;
	int FontSize = 1;
	int FontWeight = 2.5;

	if (Color == 1) {
		SelectedColor = Scalar(25, 255, 255);
	}
	else if (Color == 2) {
		SelectedColor = Scalar(255, 25, 255);
	}
	else if (Color == 3) {
		SelectedColor = Scalar(50, 50, 50);
	}
	else
	{
		SelectedColor = Scalar(255, 255, 255);
	}

	putText(SRC, //target image
		Text, //text
		Point(x, y), //top-left position
		cv::FONT_HERSHEY_COMPLEX_SMALL,
		FontSize,
		SelectedColor, //font color
		FontWeight);
	return SRC;
}




Mat ShowManyImages(Mat input1, Mat input2, Mat input3, Mat input4) {

	Size StdSize = input1.size();
	resize(input1, input1, StdSize, 0, 0, INTER_CUBIC);
	resize(input2, input2, StdSize, 0, 0, INTER_CUBIC);
	resize(input3, input3, StdSize, 0, 0, INTER_CUBIC);
	resize(input4, input4, StdSize, 0, 0, INTER_CUBIC);

	int width = 2 * input1.cols; // width of 2 images next to each other
	int height = 2 * input1.rows; // height of 2 images over reach other

	cv::Mat inputAll = cv::Mat(height, width, input1.type());

	cv::Rect subImageROI = cv::Rect(0, 0, input1.cols, input1.rows);

	// copy to subimage:
	input1.copyTo(inputAll(subImageROI));

	// move to 2nd image ROI position:
	subImageROI.x = input1.cols;
	input2.copyTo(inputAll(subImageROI));

	subImageROI.x = 0;
	subImageROI.y = input1.rows;
	input3.copyTo(inputAll(subImageROI));

	subImageROI.x = input1.cols;
	subImageROI.y = input1.rows;
	input4.copyTo(inputAll(subImageROI));


	return inputAll;
	// Create a new window, and show the Single Big Image


}



Mat ErrorDisplay(String ErrorText) {
	Mat ErrorDisplay = Mat::zeros(Size(1000, 1000), CV_8UC3);
	cv::putText(ErrorDisplay, //target image
		ErrorText, //text
		cv::Point(20, 20), //top-left position
		cv::FONT_HERSHEY_COMPLEX_SMALL,
		0.7,
		Scalar(200, 200, 200), //font color
		1);
	return ErrorDisplay;
}