// CSELECTION.cpp: 实现文件
//

#include "pch.h"
#include "TXZ.h"
#include "CSELECTION.h"
#include "afxdialogex.h"

/*
xht:
关于控件大小、位置常量的代码，迟早得统统重构
*/


// CSELECTION 对话框

IMPLEMENT_DYNAMIC(CSELECTION, CDialogEx)

CSELECTION::CSELECTION(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SELECTION, pParent)
{

}

CSELECTION::~CSELECTION()
{
}

void CSELECTION::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSELECTION, CDialogEx)
	ON_BN_CLICKED(IDC_CONFIRMBUTTON, &CSELECTION::OnBnClickedConfirmbutton)
	ON_BN_CLICKED(IDC_CANCELBUTTON, &CSELECTION::OnBnClickedCancelbutton)
END_MESSAGE_MAP()


// CSELECTION 消息处理程序


BOOL CSELECTION::OnInitDialog()
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

	// 设置窗口控件
	
	const int BUTTON_HEIGHT = (int)(DIALOG_HEIGHT * 0.1);
	const int BUTTON_WIDTH = (int)(DIALOG_WIDTH * 0.4);
	GetDlgItem(IDC_CONFIRMBUTTON)->MoveWindow((int)(DIALOG_WIDTH * 0.55), (int)(DIALOG_HEIGHT * 0.6), BUTTON_WIDTH, BUTTON_HEIGHT);
	GetDlgItem(IDC_CANCELBUTTON)->MoveWindow((int)(DIALOG_WIDTH * 0.55), (int)(DIALOG_HEIGHT * 0.75), BUTTON_WIDTH, BUTTON_HEIGHT);

	const int LIST_HEIGHT = (int)(DIALOG_HEIGHT * 0.7);
	const int LIST_WIDTH = (int)(DIALOG_WIDTH * 0.45);
	GetDlgItem(IDC_MAPLIST)->MoveWindow((int)(DIALOG_WIDTH * 0.05), (int)(DIALOG_HEIGHT * 0.05), LIST_WIDTH, LIST_HEIGHT);

	// 字体、文字大小、文字内容
	m_buttonFont.CreateFont(
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
	GetDlgItem(IDC_CANCELBUTTON)->SetFont(&m_buttonFont);
	GetDlgItem(IDC_CANCELBUTTON)->SetWindowText(_T("返回"));
	GetDlgItem(IDC_CANCELBUTTON)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CONFIRMBUTTON)->SetFont(&m_buttonFont);
	GetDlgItem(IDC_CONFIRMBUTTON)->SetWindowText(_T("确认"));
	GetDlgItem(IDC_CONFIRMBUTTON)->ShowWindow(SW_SHOW);
	

	m_listFont.CreateFont(
		(int)(LIST_HEIGHT * 0.1), // nHeight 
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
		_T("黑体")
	); // lpszFac 
	GetDlgItem(IDC_MAPLIST)->SetFont(&m_listFont);
	
	CSELECTION::InitList();

	GetDlgItem(IDC_MAPLIST)->ShowWindow(SW_SHOW);

	CSELECTION::UpdatePreview(_T("0"));
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CSELECTION::OnBnClickedCancelbutton()
{
	// TODO: 在此添加控件通知处理程序代码
	GetParent()->PostMessage(WM_TOHOMEPAGE);
}


void CSELECTION::OnBnClickedConfirmbutton()
{
	// TODO: 在此添加控件通知处理程序代码
	CListBox* myList = (CListBox*)GetDlgItem(IDC_MAPLIST);
	CString tempStr;
	myList->GetText(myList->GetCurSel(), tempStr);
	tempStr = mapPath + tempStr + _T(".txm");
	GetParent()->PostMessage(WM_TOGAME, (WPARAM)tempStr.AllocSysString());
}

BOOL CSELECTION::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		switch (pMsg->wParam)
		{
		case VK_ESCAPE:
#ifdef MYDEBUG
			MessageBox(_T("ESC"), _T("From xht"));
#endif // MYDEBUG
			OnBnClickedCancelbutton();
			return TRUE;
			break;
			/*
		case VK_RETURN:
			HWND hwnd1 = ((CEdit*)GetDlgItem(IDC_IDINPUT))->m_hWnd;
			if (pMsg->hwnd == hwnd1)
			{
				OnBnClickedConfirmbutton();
				return TRUE;
			}
			break;
			*/
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}

void CSELECTION::UpdatePreview(CString name) // 显示mapname的缩略图
{
	CStatic* pic = (CStatic*)GetDlgItem(IDC_PREVIEWIMAGE); // 预览图的控件
	pic->ShowWindow(SW_HIDE);

	CString previewImageDir; // 位图位置
	HBITMAP hBMP; // 载入的bmp

	previewImageDir = mapPath + _T("map") + name + _T(".bmp");
	hBMP = (HBITMAP)LoadImage(NULL, previewImageDir, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	if (hBMP == NULL)
	{
		// 没有缩略图就显示一个默认的defaultmap.bmp
		previewImageDir = mapPath + _T("defaultmap.bmp");
		hBMP = (HBITMAP)LoadImage(NULL, previewImageDir, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	}

	pic->SetBitmap(hBMP);

	double tempRatio;
	CRect tempRect;
	pic->GetClientRect(tempRect);
	tempRatio = (double)tempRect.Height() / (double)tempRect.Width();

	GetClientRect(tempRect);
	const int DIALOG_HEIGHT = tempRect.Height();
	const int DIALOG_WIDTH = tempRect.Width();
	const int PREVIEW_SIZE = min((int)(DIALOG_HEIGHT * 0.4), (int)(DIALOG_WIDTH * 0.4));

	int tempHeight, tempWidth;
	if (tempRatio > 1)
	{
		tempHeight = PREVIEW_SIZE;
		tempWidth = (int)(PREVIEW_SIZE / tempRatio);
	}
	else
	{
		tempHeight = (int)(PREVIEW_SIZE * tempRatio);
		tempWidth = PREVIEW_SIZE;
	}
	
	pic->MoveWindow((int)(DIALOG_WIDTH * 0.55) + (PREVIEW_SIZE - tempWidth) / 2, (int)(DIALOG_HEIGHT * 0.05) + (PREVIEW_SIZE - tempHeight) / 2, tempWidth, tempHeight, TRUE);
	pic->ShowWindow(SW_SHOW);
}

void CSELECTION::InitList()
{
	CFileFind tempFind;
	BOOL IsFind = tempFind.FindFile(mapPath + _T("/*.txm"));
	CListBox* myList = (CListBox*)GetDlgItem(IDC_MAPLIST);

	myList->ResetContent();
	while (IsFind)
	{
		IsFind = tempFind.FindNextFile(); // 找到最后一个文件时返回FALSE
		if (tempFind.IsDots() || tempFind.IsDirectory())
		{
			continue;
		}
		CString filename = tempFind.GetFileName();
		filename = filename.Left(filename.ReverseFind('.'));
		myList->AddString(filename);
	}
	if (myList->GetCount() > 0)
	{
		myList->SetCurSel(0);
	}
	else
	{
		GetDlgItem(IDC_CONFIRMBUTTON)->EnableWindow(FALSE);
	}
}