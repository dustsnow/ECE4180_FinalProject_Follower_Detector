// follower_detection.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "follower_detection.h"
#include "opencv2/opencv.hpp"
using namespace cv;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: If this DLL is dynamically linked against the MFC DLLs,
//		any functions exported from this DLL which call into
//		MFC must have the AFX_MANAGE_STATE macro added at the
//		very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

// Cfollower_detectionApp

BEGIN_MESSAGE_MAP(Cfollower_detectionApp, CWinApp)
END_MESSAGE_MAP()


// Cfollower_detectionApp construction

Cfollower_detectionApp::Cfollower_detectionApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
	this->err_code = ERR_PERSON_LOST;
	this->Circle1_LowerH = 157;
	this->Circle1_LowerS = 149;
	this->Circle1_LowerV = 66;
	this->Circle1_UpperH = 180;
	this->Circle1_UpperS = 256;
	this->Circle1_UpperV = 125;
	this->Circle1_HC_Param1 = 200;
	this->Circle1_HC_Param2 = 30;

	this->Circle2_LowerH = 157;
	this->Circle2_LowerS = 149;
	this->Circle2_LowerV = 66;
	this->Circle2_UpperH = 180;
	this->Circle2_UpperS = 256;
	this->Circle2_UpperV = 125;
	this->Circle2_HC_Param1 = 200;
	this->Circle2_HC_Param2 = 30;

	this->Circle3_LowerH = 157;
	this->Circle3_LowerS = 149;
	this->Circle3_LowerV = 66;
	this->Circle3_UpperH = 180;
	this->Circle3_UpperS = 256;
	this->Circle3_UpperV = 125;
	this->Circle3_HC_Param1 = 200;
	this->Circle3_HC_Param2 = 30;
}


// The one and only Cfollower_detectionApp object

Cfollower_detectionApp theApp;


// Cfollower_detectionApp initialization

BOOL Cfollower_detectionApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}
// Return: false if cannot start
bool Cfollower_detectionApp::Cfollower_detectionApp_start()
{
	VideoCapture cap(0); // open the video camera no. 0
	Mat frame,img_hsv,img_mask;
	int circle_detected;
	if(!cap.isOpened())
    {
		this->err_msg = "Cannot open camera";
		this->err_code = ERR_CAMERA_FAIL;
		return false;
	}
	while(1){
		circle_detected = 0;
		cap >> frame;
		if(!frame.data){
            this->err_msg = "frame capture error";
			this->err_code = ERR_CAPTURE_FAIL;
        }
		cvtColor(frame, img_hsv, CV_BGR2HSV);

		// Detect Circle 1
		inRange(img_hsv,cv::Scalar(Circle1_LowerH,Circle1_LowerS,Circle1_LowerV), cv::Scalar(Circle1_UpperH,Circle1_UpperS,Circle1_UpperV),img_mask);
		GaussianBlur(img_mask, img_mask, cv::Size(9,9),2,2);
		std::vector<cv::Vec3f> circles;
		HoughCircles(img_mask, circles, CV_HOUGH_GRADIENT,1,img_mask.rows/8,Circle1_HC_Param1,Circle1_HC_Param2,0,0);
		if(circles.size() > 0) circle_detected++;

		// Detect Circle 2
		inRange(img_hsv,cv::Scalar(Circle2_LowerH,Circle2_LowerS,Circle2_LowerV), cv::Scalar(Circle2_UpperH,Circle2_UpperS,Circle2_UpperV),img_mask);
		GaussianBlur(img_mask, img_mask, cv::Size(9,9),2,2);
		HoughCircles(img_mask, circles, CV_HOUGH_GRADIENT,1,img_mask.rows/8,Circle2_HC_Param1,Circle2_HC_Param2,0,0);
		if(circles.size() > 0) circle_detected++;

		// Detect Circle 3
		inRange(img_hsv,cv::Scalar(Circle3_LowerH,Circle3_LowerS,Circle3_LowerV), cv::Scalar(Circle3_UpperH,Circle3_UpperS,Circle3_UpperV),img_mask);
		GaussianBlur(img_mask, img_mask, cv::Size(9,9),2,2);
		HoughCircles(img_mask, circles, CV_HOUGH_GRADIENT,1,img_mask.rows/8,Circle3_HC_Param1,Circle3_HC_Param2,0,0);
		if(circles.size() > 0) circle_detected++;

		if(circle_detected < 2) this->err_msg = "Person Lost";

		waitKey(10);
	}
	return true;
}