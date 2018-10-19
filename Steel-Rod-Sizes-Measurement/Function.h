#pragma once
#include <opencv2\opencv.hpp>
#include <opencv2\cvconfig.h>

using namespace std;
using namespace cv;

Mat ShowManyImages(Mat, Mat, Mat, Mat);
Mat ErrorDisplay(String);
Mat PutTextOnMe(Mat, String, int, int, int);
String TwoDecimalString(String);
double GetInput(double);
double RightTriangle(int, int);