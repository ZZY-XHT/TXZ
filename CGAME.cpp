// CGAME.cpp: 实现文件
//

#include "pch.h"
#include "TXZ.h"
#include "CGAME.h"
#include "afxdialogex.h"
#include "CGAME_Display.h"
#include "CGAME_Map.h"

CGAME_Display* myDisplay;
CGAME_Map* myMap;

// CGAME 对话框

IMPLEMENT_DYNAMIC(CGAME, CDialogEx)

CGAME::CGAME(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GAME, pParent)
{

}

CGAME::~CGAME()
{
}

void CGAME::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CGAME, CDialogEx)
	ON_BN_CLICKED(IDC_RETURN, &CGAME::OnBnClickedReturn)
	ON_MESSAGE(WM_STARTGAME, &CGAME::StartGame)
END_MESSAGE_MAP()


// CGAME 消息处理程序


BOOL CGAME::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	// 设置窗口

	// 满屏代码
	CRect ClientRect;
	GetParent()->GetClientRect(ClientRect);
	MoveWindow(ClientRect);
	const int DIALOG_HEIGHT = ClientRect.Height();
	const int DIALOG_WIDTH = ClientRect.Width();

	this->SetBackgroundColor(RGB(255, 255, 0), TRUE);
	/*
	CString str;
	str.Format(_T("Height is %d, Weight is %d"), DIALOG_HEIGHT, DIALOG_WIDTH);
	MessageBox(str, _T("xht"));
	*/

	// 设置控件大小、位置
	const int BUTTON_HEIGHT = (int)(DIALOG_HEIGHT * 0.1);
	const int BUTTON_WIDTH = BUTTON_HEIGHT * 2;
	GetDlgItem(IDC_RETURN)->MoveWindow(0, 0, BUTTON_WIDTH, BUTTON_HEIGHT, TRUE);

	myDisplay = new CGAME_Display;
	myDisplay->Create(IDD_DISPLAY, this);
	myDisplay->MoveWindow(0, (int)(DIALOG_HEIGHT * 0.1), DIALOG_WIDTH, (int)(DIALOG_HEIGHT * 0.9));
	myDisplay->ShowWindow(SW_SHOW);

	//创建Map
	myMap = new CGAME_Map(myDisplay);
	
	// 设置窗口按钮
	/*
	字体、文字大小、文字内容
	按钮大小、按钮位置
	焦点位置
	*/

	// 字体、文字大小、文字内容
	m_font.CreateFont(
		(int)(BUTTON_HEIGHT * 0.6), // nHeight 
		0, // nWidth 
		0, // nEscapement 
		0, // nOrientation 
		//FW_BOLD, // nWeight 
		FW_NORMAL, // nWeight 
		FALSE, // bItalic 
		FALSE, // bUnderline 
		FALSE, // cStrikeOut 
		//ANSI_CHARSET, // nCharSet 
		GB2312_CHARSET, // nCharSet 
		OUT_DEFAULT_PRECIS, // nOutPrecision 
		CLIP_DEFAULT_PRECIS, // nClipPrecision 
		DEFAULT_QUALITY, // nQuality 
		DEFAULT_PITCH | FF_SWISS, // nPitchAndFamily 
		_T("隶书")
	); // lpszFac 
	/*
	字符集：
	中文用GB2312_CHARSET，或谨慎地使用DEFAULT_CHARSET
	建议字体：
	中文用黑体、隶书、华文琥珀、华文行楷
	*/
	GetDlgItem(IDC_RETURN)->SetFont(&m_font);
	GetDlgItem(IDC_RETURN)->SetWindowText(_T("返回"));

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void CGAME::OnBnClickedReturn()
{
	// TODO: 在此添加控件通知处理程序代码
	myDisplay->Clear();
	GetParent()->PostMessage(WM_TOSELECTION);
}

BOOL CGAME::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		switch (pMsg->wParam)
		{
#ifdef MYDEBUG
		case VK_F2:
		{
			MessageBox(_T("w"), _T("From xht"));
			CStatic* pic2 = new CStatic();
			pic2->Create(NULL, SS_BITMAP, CRect(0, 100, 200, 300), this);

			HBITMAP hbmp;
			CBitmap bitmap;
			bitmap.LoadBitmap(IDB_P_MAP0);
			hbmp = (HBITMAP)bitmap.GetSafeHandle();
			pic2->SetBitmap(hbmp);
			pic2->MoveWindow(0, 0, 700, 700);
			pic2->ShowWindow(SW_SHOW);
			UpdateWindow();
			MessageBox(_T("ww"), _T("From xht"));
			delete pic2;
			//
			break;
		}
#endif // MYDEBUG
		case 'W':
		case VK_UP:
#ifdef MYDEBUG
			MessageBox(_T("UP"), _T("From xht"));
#endif // MYDEBUG
			myMap->MovePlayer(DIR_UP);
			break;
		case 'S':
		case VK_DOWN:
#ifdef MYDEBUG
			MessageBox(_T("DOWN"), _T("From xht"));
#endif // MYDEBUG
			myMap->MovePlayer(DIR_DOWN);
			break;
		case 'A':
		case VK_LEFT:
#ifdef MYDEBUG
			MessageBox(_T("LEFT"), _T("From xht"));
#endif // MYDEBUG
			myMap->MovePlayer(DIR_LEFT);
			break;
		case 'D':
		case VK_RIGHT:
#ifdef MYDEBUG
			MessageBox(_T("RIGHT"), _T("From xht"));
#endif // MYDEBUG
			myMap->MovePlayer(DIR_RIGHT);
			break;
		case VK_ESCAPE:
#ifdef MYDEBUG
				MessageBox(_T("ESC"), _T("From xht"));
#endif // MYDEBUG
			OnBnClickedReturn();
			break;
		case VK_RETURN:
#ifdef MYDEBUG
			MessageBox(_T("RETURN"), _T("From xht"));
#endif // MYDEBUG
		default:
			return CDialogEx::PreTranslateMessage(pMsg);
		}
		return TRUE;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}
LRESULT CGAME::StartGame(WPARAM wParam, LPARAM lParam)
{
	// 根据指令开始游戏
	// 释放wParam的内存
	BSTR b = (BSTR)wParam;
	CString s(b);
	SysFreeString(b);
	return myMap->SetMap(s);
}



BOOL CGAME::DestroyWindow()
{
	// TODO: 在此添加专用代码和/或调用基类
	myDisplay->DestroyWindow();
	delete myDisplay;
	return CDialogEx::DestroyWindow();
}