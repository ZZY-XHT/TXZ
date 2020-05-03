// CGAME.cpp: 实现文件
//

#include "pch.h"
#include "TXZ.h"
#include "CGAME.h"
#include "afxdialogex.h"

// CGAME 对话框

IMPLEMENT_DYNAMIC(CGAME, CDialogEx)

CGAME::CGAME(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GAME, pParent),
	m_step(0), m_ss(0), m_mm(0), m_Timer(NULL),
	myDisplay(NULL), myMap(NULL)
{

}

CGAME::~CGAME()
{
}

//步数

void CGAME::InitStepAndTimer()
{
	m_step = 0;
	m_ss = 0;
	m_mm = 0;
	if (m_Timer != NULL) KillTimer(m_Timer);
	m_Timer = SetTimer(0, 1000, NULL);
	GetDlgItem(IDC_GAME_TEXT_STEP)->SetWindowTextW(_T("步数：0"));
	GetDlgItem(IDC_GAME_TEXT_TIME)->SetWindowTextW(_T("时间：0s"));
}

void CGAME::IncrementStep(BOOL moved)
{
	if (moved)
	{
		CString text;
		text.Format(_T("步数：%d"), ++m_step);
		GetDlgItem(IDC_GAME_TEXT_STEP)->SetWindowText(text);
	}
}

void CGAME::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CGAME, CDialogEx)
	ON_MESSAGE(WM_STARTGAME, &CGAME::StartGame)
	ON_BN_CLICKED(IDC_GAME_RESTARTBUTTON, &CGAME::OnBnClickedGameRestartbutton)
	ON_BN_CLICKED(IDC_GAME_RETURNBUTTON, &CGAME::OnBnClickedGameReturnbutton)
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CGAME 消息处理程序

void CGAME::OnTimer(UINT_PTR nIdEvent)
{
	if (myMap->IsFinished())
	{
		KillTimer(m_Timer);
	}
	else
	{
		CString text;
		m_ss++;
		if (m_ss == 60)
		{
			m_mm++;
			m_ss = 0;
		}

		if (m_mm > 0) text.Format(_T("时间：%dmin%ds"), m_mm, m_ss);
		else text.Format(_T("时间：%ds"), m_ss);

		GetDlgItem(IDC_GAME_TEXT_TIME)->SetWindowText(text);
	}
}

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
	GetDlgItem(IDC_GAME_RETURNBUTTON)->MoveWindow(0, 0, BUTTON_WIDTH, BUTTON_HEIGHT, TRUE);
	GetDlgItem(IDC_GAME_RESTARTBUTTON)->MoveWindow(BUTTON_WIDTH, 0, BUTTON_WIDTH, BUTTON_HEIGHT, TRUE);
	GetDlgItem(IDC_GAME_TEXT_STEP)->MoveWindow((int)(2 * BUTTON_WIDTH), 0, (int)(1.5 * BUTTON_WIDTH), BUTTON_HEIGHT, TRUE);
	GetDlgItem(IDC_GAME_TEXT_TIME)->MoveWindow((int)(3.5 *BUTTON_WIDTH), 0, (int)(1.5 * BUTTON_WIDTH), BUTTON_HEIGHT, TRUE);
	// 创建Display
	myDisplay = new CGAME_Display(CRect(0, (int)(DIALOG_HEIGHT * 0.1), DIALOG_WIDTH, DIALOG_HEIGHT));
	myDisplay->Create(IDD_DISPLAY, this);

	// 创建Map
	myMap = new CGAME_Map(myDisplay);

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
	GetDlgItem(IDC_GAME_RETURNBUTTON)->SetFont(&m_font);
	GetDlgItem(IDC_GAME_RETURNBUTTON)->SetWindowText(_T("返回"));
	GetDlgItem(IDC_GAME_RESTARTBUTTON)->SetFont(&m_font);
	GetDlgItem(IDC_GAME_RESTARTBUTTON)->SetWindowText(_T("重玩"));
	GetDlgItem(IDC_GAME_TEXT_STEP)->SetFont(&m_font);
	GetDlgItem(IDC_GAME_TEXT_TIME)->SetFont(&m_font);

	GetDlgItem(IDC_GAME_TEXT_TIME)->ShowWindow(TRUE);
	GetDlgItem(IDC_GAME_TEXT_STEP)->ShowWindow(TRUE);
	GetDlgItem(IDC_GAME_RETURNBUTTON)->ShowWindow(TRUE);
	GetDlgItem(IDC_GAME_RESTARTBUTTON)->ShowWindow(TRUE);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void CGAME::OnBnClickedGameReturnbutton()
{
	// TODO: 在此添加控件通知处理程序代码
	myDisplay->Clear();
	GetParent()->PostMessage(WM_TOSELECTION);
}

void CGAME::OnBnClickedGameRestartbutton()
{
	// TODO: 在此添加控件通知处理程序代码
	InitStepAndTimer();
	myMap->Restart();
}

BOOL CGAME::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		BOOL moved = FALSE;
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
			IncrementStep(moved = myMap->MovePlayer(DIR_UP));
			break;
		case 'S':
		case VK_DOWN:
			IncrementStep(moved = myMap->MovePlayer(DIR_DOWN));
			break;
		case 'A':
		case VK_LEFT:
			IncrementStep(moved = myMap->MovePlayer(DIR_LEFT));
			break;
		case 'D':
		case VK_RIGHT:
			IncrementStep(moved = myMap->MovePlayer(DIR_RIGHT));
			break;
		case VK_ESCAPE:
			OnBnClickedGameReturnbutton();
			break;
		case VK_RETURN:
		default:
			return CDialogEx::PreTranslateMessage(pMsg);
		}
		if (moved && myMap->IsFinished())
		{
			MessageBox(_T("恭喜闯关成功！"), _T("From xht"));
		}
		return TRUE;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}

LRESULT CGAME::StartGame(WPARAM wParam, LPARAM lParam)
{
	// 根据指令开始游戏
	// 释放wParam的内存
	InitStepAndTimer();
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
	delete myMap;
	if(m_Timer != NULL)
		KillTimer(m_Timer);
	return CDialogEx::DestroyWindow();
}