#include "opencv2/imgcodecs.hpp"
#include <opencv2/opencv.hpp>
#include <opencv2/cvconfig.h>
#include <opencv2/opencv_modules.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <iostream>
#include <vector>
#include "Function.h"
#include "Reference.h"

using namespace cv;
using namespace std;

using std::vector;
using std::to_string;

Mat ShowManyImages(Mat, Mat, Mat, Mat);
Mat ErrorDisplay(String);
double Reference();
double ChangeInDistance(int, int, double);
int CurrentDistance();
Mat PutTextOnMe(Mat, String, int, int, int);
String TwoDecimalString(double);
double GetDecrementReference(double);
double GetIncrementReference(double);

int main()
{
	VideoCapture capWebcam(1);
	//double Referrence = GetInput(Reference());
	double Referrence = 1;

	Scalar color = Scalar(255, 25, 255);
	String Tracker = "TrackBarWindow";
	int threshold_value = 0;
	int threshold_type = 3;
	int const max_value = 255;
	int const max_type = 4;
	int const max_binary_value = 255;
	int blurValue = 5;
	int maxblur = 15;

	Mat SRC, SmoothImage, Drawing, Masker, Final, Display;

	namedWindow(Tracker);
	createTrackbar("Threshod Type", Tracker, &threshold_type, max_type);
	createTrackbar("Threshod Value", Tracker, &threshold_value, max_value);
	createTrackbar("Blur Value", Tracker, &blurValue, maxblur);

	if (capWebcam.isOpened() == false)
	{
		cout << "WebCam Cannot be read" << endl;
		return(0);
	}

	while (capWebcam.isOpened())
	{
		bool blnframe = capWebcam.read(SRC);
		capWebcam.read(Display);
		Size OrgSize = SRC.size();

		Drawing = Mat::zeros(SRC.size(), CV_8UC3);
		Masker = cv::Mat::zeros(SRC.rows + 2, SRC.cols + 2, CV_8U);

		Mat CVTColor;
		cvtColor(SRC, CVTColor, COLOR_BGR2GRAY);

		Mat GaussiBlur;
		GaussianBlur(CVTColor, GaussiBlur, Size(5, 5), 1);

		if (blurValue == 0) {
			blurValue = 1;
		}

		Mat blurMe;
		blur(GaussiBlur, blurMe, Size(blurValue, blurValue));

		Mat thresholdImage;
		threshold(blurMe, thresholdImage, threshold_value, max_binary_value, threshold_type);


		Mat mask = thresholdImage.clone();

		dilate(mask, mask, cv::Mat());
		dilate(mask, mask, cv::Mat());

		erode(mask, mask, cv::Mat());
		erode(mask, mask, cv::Mat());

		erode(mask, mask, cv::Mat());
		erode(mask, mask, cv::Mat());

		dilate(mask, mask, cv::Mat());
		dilate(mask, mask, cv::Mat());

		Mat median;
		medianBlur(mask, median, 7);

		SmoothImage = median;

		floodFill(median, Masker, cv::Point(0, 0), 255, 0, cv::Scalar(), cv::Scalar(), 4 + (255 << 8) + cv::FLOODFILL_MASK_ONLY);

		Masker(Range(1, Masker.rows - 1), Range(1, Masker.cols - 1)).copyTo(Final);

		Mat imageCanny;
		Canny(median, imageCanny, 100, 200, 3);

		vector<vector<Point>> contours;
		vector<Vec4i> hierarchy;

		findContours(imageCanny, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_NONE, Point(0, 0));

		vector<vector<Point> > contours_poly(contours.size());
		vector<Rect> boundRect(contours.size());
		vector<Point2f>center(contours.size());
		vector<float>radius(contours.size());
		vector<RotatedRect> minRect(contours.size());

		for (int i = 0; i < contours.size(); i++) {
			approxPolyDP(Mat(contours[i]), contours_poly[i], 3, true);
			boundRect[i] = boundingRect(Mat(contours_poly[i]));
			minEnclosingCircle((Mat)contours_poly[i], center[i], radius[i]);
			minRect[i] = minAreaRect(Mat(contours[i]));
		}

		int DistanceBetweenText = 20;
		int RectID = 1;

		String screenSize = "WxH = " + TwoDecimalString(OrgSize.height * Referrence) + " x " + TwoDecimalString(OrgSize.width * Referrence);

		PutTextOnMe(Display, screenSize, 1, 20, 50);

		for (int i = 0; i < contours.size(); i++)
		{
			if ((boundRect[i].width)*Referrence > 25 && (boundRect[i].height*Referrence) > 25) {

				drawContours(Drawing, contours_poly, i, color, FILLED, 8, vector<Vec4i>(), 0, Point());
				rectangle(Display, boundRect[i].tl(), boundRect[i].br(), color, 2, 8, 0);

				vector<int> RectPoints;
				Point2f rect_points[4]; minRect[i].points(rect_points);
				//for (int j = 0; j < 4; j++) {
				//	line(Display, rect_points[j], rect_points[(j + 1) % 4], Scalar(255, 255, 55), 2, 8);
				//}
				//float x1 = rect_points[0].x;
				//float y1 = rect_points[0].y;
				//float x2 = rect_points[1].x;
				//float y2 = rect_points[1].y;
				//float x3 = rect_points[2].x;
				//float y3 = rect_points[2].y;
				//float x4 = rect_points[3].x;
				//float y4 = rect_points[3].y;

				//cout << x1 << " <1> " << y1 << " -- " << x2 << " <2> " << y2 << " -- " << x3 << " <3> " << y3 << " -- " << x4 << " <4> " << y4 << endl;

				double Height = boundRect[i].height*Referrence;
				double Width = boundRect[i].width*Referrence;

				String StringID = "Ob-" + std::to_string(RectID);
				String MySize = StringID + " W-" + TwoDecimalString(Width) + " H-" + TwoDecimalString(Height);

				PutTextOnMe(Display, StringID, 1, boundRect[i].x + 20, boundRect[i].y + 50);
				PutTextOnMe(Display, MySize, 2, OrgSize.width - 320, DistanceBetweenText);

				RectID++;
				DistanceBetweenText = DistanceBetweenText + 20;

			}

		}
		PutTextOnMe(SRC, "SRC", 1, 20, 20);
		PutTextOnMe(Drawing, "Drawing", 1, 20, 20);
		PutTextOnMe(Display, "Display", 1, 20, 20);
		PutTextOnMe(Final, "Final", 1, 20, 20);

		namedWindow("Modification Display", WINDOW_NORMAL);
		imshow("Modification Display", ShowManyImages(SRC, Drawing, Display, Drawing));

		namedWindow("Final", WINDOW_NORMAL);
		imshow("Final", Final);

		namedWindow("DisplyScreen", WINDOW_NORMAL);
		imshow("DisplyScreen", Display);

		waitKey(21);
	}
	return(0);
}