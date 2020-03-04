
// TXZ.h: PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含 'pch.h' 以生成 PCH"
#endif

#include "resource.h"		// 主符号


// CTXZApp:
// 有关此类的实现，请参阅 TXZ.cpp
//

class CTXZApp : public CWinApp
{
public:
	CTXZApp();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern CTXZApp theApp;

extern CString mapPath;
extern CString resPath;
extern CString appPath;