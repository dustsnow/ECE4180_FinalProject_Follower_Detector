// follower_detection.h : main header file for the follower_detection DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols
#include <string>

#define ERR_PERSON_LOST 1
// Cfollower_detectionApp
// See follower_detection.cpp for the implementation of this class
//

class Cfollower_detectionApp : public CWinApp
{
public:
	Cfollower_detectionApp();
	int err_code;
	std::string err_msg;
	int Circle1_LowerH;
	int Circle1_LowerS;
	int Circle1_LowerV;
	int Circle1_UpperH;
	int Circle1_UpperS;
	int Circle1_UpperV ;
	int Circle1_HC_Param1;
	int Circle1_HC_Param2;

	int Circle2_LowerH;
	int Circle2_LowerS;
	int Circle2_LowerV;
	int Circle2_UpperH;
	int Circle2_UpperS;
	int Circle2_UpperV ;
	int Circle2_HC_Param1;
	int Circle2_HC_Param2;

	int Circle3_LowerH;
	int Circle3_LowerS;
	int Circle3_LowerV;
	int Circle3_UpperH;
	int Circle3_UpperS;
	int Circle3_UpperV ;
	int Circle3_HC_Param1;
	int Circle3_HC_Param2;

	__declspec(dllexport) bool Cfollower_detectionApp_start();
// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()

};
