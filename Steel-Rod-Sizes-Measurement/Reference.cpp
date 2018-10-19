#include <opencv2\opencv.hpp>
#include <opencv2\cvconfig.h>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include "Reference.h"
using namespace cv;
using namespace std;


int MidPoint = 300;
double OriginalImageSize = 105;
double ImageSizeinPixcel = 434;
double DiffernceFor1mm = 0.0012;
double ChangeInImageSizeinPixcelOnIncrement = 362;
double ChangeInImageSizeinPixcelOnDecrement = 542;
double DecrementDistance = 60;
double IncrementDistance = 60;


double GetInput(double Referrence) {
	int CurrentMidDistance = CurrentDistance();

	cout << "-----------------------------------------------------------------------------------------------------------------" << endl;
	cout << "Current Reference  =  " << Referrence << endl;
	cout << "Reference Differents for 1cm Increment in Movement = " << GetIncrementReference(Referrence) << endl;
	cout << "Reference Differents for 1cm Decrement in Movement = " << GetDecrementReference(Referrence) << endl;
	cout << "Current distance between object and camera is " << CurrentMidDistance << "cm" << endl;
	cout << "Do you want to increase or decrease the distance ? " << endl
		<< "For Yes = 1 and No = 2  " << endl;
	int YesOrNo;
	cin >> YesOrNo;
	if (YesOrNo == 1) {
		cout << "Select an Option " << endl
			<< "Increment = 1 and Decrement = 2 " << endl;
		int AddOrSub;
		cin >> AddOrSub;
		int ChangeVal;
		if (AddOrSub == 1 || AddOrSub == 2) {
			cout << "Enter the change value in cm " << endl;
			cin >> ChangeVal;
			Referrence = ChangeInDistance(AddOrSub, ChangeVal, Referrence);
			cout << "-----------------------------------------------------------------------------------------------------------------" << endl;
			cout << "Updated Reference  =  " << Referrence << endl;
			cout << "-----------------------------------------------------------------------------------------------------------------" << endl;
			return Referrence;
		}
		else {
			cout << "-----------------------------------------------------------------------------------------------------------------" << endl;
			cout << "Input Value id incorrect";
			cout << "-----------------------------------------------------------------------------------------------------------------" << endl;
			return Referrence;
		}
	}
	else
	{
		cout << "-----------------------------------------------------------------------------------------------------------------" << endl;
		return Referrence;
		cout << "-----------------------------------------------------------------------------------------------------------------" << endl;
	}
}




double Reference() {
	double ReferencNumber = OriginalImageSize / ImageSizeinPixcel;
	return ReferencNumber;
}

int CurrentDistance() {
	return MidPoint;
}

double GetIncrementReference(double Refer) {
	double IncrementReference = OriginalImageSize / ChangeInImageSizeinPixcelOnIncrement;
	double IncrementDifferents = IncrementReference - Refer;
	double IncrementDiffernceFor1cm = IncrementDifferents / IncrementDistance;
	return IncrementDiffernceFor1cm;
}

double GetDecrementReference(double Refer) {
	double DecrementReference = OriginalImageSize / ChangeInImageSizeinPixcelOnDecrement;
	double DecrementDifferents = Refer - DecrementReference;
	double DecrementDiffernceFor1cm = DecrementDifferents / DecrementDistance;
	return DecrementDiffernceFor1cm;
}

double ChangeInDistance(int Sign, int Value, double Refer) {
	double FinalVal;
	double ChangeValueIncrement = GetIncrementReference(Refer) * Value;
	double ChangeValueDecrement = GetDecrementReference(Refer) * Value;

	if (Sign == 2) {
		FinalVal = Refer + ChangeValueIncrement;
	}
	else if (Sign == 1) {
		FinalVal = Refer - ChangeValueDecrement;
	}
	else {
		FinalVal = 1;
	}
	return FinalVal;
}