// CHOMEPAGE.cpp: 实现文件
//

#include "pch.h"
#include "TXZ.h"
#include "CHOMEPAGE.h"
#include "afxdialogex.h"


// CHOMEPAGE 对话框

IMPLEMENT_DYNAMIC(CHOMEPAGE, CDialogEx)

CHOMEPAGE::CHOMEPAGE(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_HOMEPAGE, pParent)
{

}

CHOMEPAGE::~CHOMEPAGE()
{
}

void CHOMEPAGE::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CHOMEPAGE, CDialogEx)
	ON_BN_CLICKED(IDC_STARTGAME, &CHOMEPAGE::OnBnClickedStartgame)
	ON_BN_CLICKED(IDC_EXITGAME, &CHOMEPAGE::OnBnClickedExitgame)
END_MESSAGE_MAP()


// CHOMEPAGE 消息处理程序


BOOL CHOMEPAGE::OnInitDialog()
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

	/*
	CString str;
	str.Format(_T("Height is %d, Weight is %d"), DIALOG_HEIGHT, DIALOG_WIDTH);
	MessageBox(str, _T("xht"));
	*/

	// 设置窗口按钮
	/*
	字体、文字大小、文字内容
	按钮大小、按钮位置
	焦点位置
	*/

	// 字体、文字大小、文字内容
	CFont* f;
	f = new CFont;
	f->CreateFont(
		56, // nHeight 
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
		_T("华文琥珀")
	); // lpszFac 
	/*
	字符集：
	中文用GB2312_CHARSET，或谨慎地使用DEFAULT_CHARSET
	建议字体：
	中文用黑体、隶书、华文琥珀、华文行楷
	*/
	GetDlgItem(IDC_STARTGAME)->SetFont(f);
	GetDlgItem(IDC_STARTGAME)->SetWindowText(_T("开始游戏"));
	GetDlgItem(IDC_EXITGAME)->SetFont(f);
	GetDlgItem(IDC_EXITGAME)->SetWindowText(_T("结束游戏"));

	// 设置按钮大小、位置
	const int BUTTON_HEIGHT = 120;
	const int BUTTON_WIDTH = 250;
	GetDlgItem(IDC_STARTGAME)->MoveWindow((DIALOG_WIDTH - BUTTON_WIDTH) / 2, DIALOG_HEIGHT / 3 - BUTTON_HEIGHT / 2, BUTTON_WIDTH, BUTTON_HEIGHT, TRUE);
	GetDlgItem(IDC_EXITGAME)->MoveWindow((DIALOG_WIDTH - BUTTON_WIDTH) / 2, DIALOG_HEIGHT / 3 * 2 - BUTTON_HEIGHT / 2, BUTTON_WIDTH, BUTTON_HEIGHT, TRUE);

	// 设置焦点
	// GetDlgItem(IDC_STARTGAME)->SetFocus();

	return TRUE;
	//return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void CHOMEPAGE::OnBnClickedStartgame()
{
	// TODO: 在此添加控件通知处理程序代码
	MessageBox(_T("Hello"), _T("From xht"));
	GetParent()->PostMessage(WM_TOSELECTION);
}


void CHOMEPAGE::OnBnClickedExitgame()
{
	// TODO: 在此添加控件通知处理程序代码
	MessageBox(_T("Byebye"), _T("From xht"));
	GetParent()->PostMessage(WM_CLOSE);
	//GetParent()->DestroyWindow();
}

BOOL CHOMEPAGE::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		switch (pMsg->wParam)
		{
		case VK_ESCAPE:
			OnBnClickedExitgame();
			break;
		default:
			return CDialogEx::PreTranslateMessage(pMsg);
		}
		return TRUE;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}