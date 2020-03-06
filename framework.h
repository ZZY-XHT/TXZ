﻿#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 从 Windows 头中排除极少使用的资料
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 某些 CString 构造函数将是显式的

// 关闭 MFC 的一些常见且经常可放心忽略的隐藏警告消息
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC 核心组件和标准组件
#include <afxext.h>         // MFC 扩展


#include <afxdisp.h>        // MFC 自动化类



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC 对 Internet Explorer 4 公共控件的支持
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC 对 Windows 公共控件的支持
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // MFC 支持功能区和控制条

// 自定义DEBUG
#ifdef DEBUG
// #define MYDEBUG
#endif // DEBUG

// 自定义常量
#define MAXMAPSIZE 30

// 自定义消息
#define WM_TOGAME WM_USER+1
#define WM_TOHOMEPAGE WM_USER+2
#define WM_STARTGAME WM_USER+3
#define WM_TOSELECTION WM_USER+4
#define WM_UPDATE WM_USER+5

// 自定义地图格子状态
#define MP_NULL 0
#define MP_BOX 1
#define MP_GOAL 2
#define MP_FINISH 3
#define MP_WALL 4
#define MP_FIRST 0
#define MP_LAST 4

// 自定义图标常数
#define PICNUM 6
#define PIC_NULL 0
#define PIC_BOX 1
#define PIC_GOAL 2
#define PIC_FINISH 3
#define PIC_WALL 4
#define PIC_PLAYER 5

#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif

