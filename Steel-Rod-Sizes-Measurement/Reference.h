#pragma once
#include <opencv2\opencv.hpp>
#include <opencv2\cvconfig.h>

using namespace std;
using namespace cv;

double Reference();
double ChangeInDistance(int, int, double);
int CurrentDistance();
double GetDecrementReference(double);
double GetIncrementReference(double);