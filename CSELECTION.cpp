// CSELECTION.cpp: 实现文件
//

#include "pch.h"
#include "TXZ.h"
#include "CSELECTION.h"
#include "afxdialogex.h"

const int PREVIEW_SIZE = 300;
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

	/*
	CString str;
	str.Format(_T("Height is %d, Weight is %d"), DIALOG_HEIGHT, DIALOG_WIDTH);
	MessageBox(str, _T("xht"));
	*/

	// 设置窗口控件
	/*
	字体、文字大小、文字内容
	大小、位置
	焦点位置
	*/

	// 字体、文字大小、文字内容
	CFont* f;
	f = new CFont;
	f->CreateFont(
		42, // nHeight 
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
	GetDlgItem(IDC_CANCELBUTTON)->SetFont(f);
	GetDlgItem(IDC_CANCELBUTTON)->SetWindowText(_T("返回"));
	GetDlgItem(IDC_CONFIRMBUTTON)->SetFont(f);
	GetDlgItem(IDC_CONFIRMBUTTON)->SetWindowText(_T("确认"));
	GetDlgItem(IDC_TEXT1)->SetFont(f);
	GetDlgItem(IDC_TEXT1)->SetWindowText(_T("请输入关卡编号：我1111111"));
	GetDlgItem(IDC_IDINPUT)->SetFont(f);
	GetDlgItem(IDC_IDINPUT)->SetWindowText(_T("0"));

	// 设置大小、位置
	const int TEXT_OFFSETX = 75;
	const int TEXT_OFFSETY = 120;
	const int TEXT_HEIGHT = 36;
	const int TEXT_WIDTH = 340;
	const int INPUT_HEIGHT = 40;
	const int INPUT_WIDTH = 80;
	GetDlgItem(IDC_TEXT1)->MoveWindow(TEXT_OFFSETY, TEXT_OFFSETX, TEXT_WIDTH, TEXT_HEIGHT, TRUE);
	GetDlgItem(IDC_IDINPUT)->MoveWindow(TEXT_OFFSETY + TEXT_WIDTH, TEXT_OFFSETX, INPUT_WIDTH, INPUT_HEIGHT, TRUE);

	const int BUTTON_OFFSETX = 520;
	const int BUTTON_HEIGHT = 70;
	const int BUTTON_WIDTH = 140;
	GetDlgItem(IDC_CONFIRMBUTTON)->MoveWindow(DIALOG_WIDTH / 3 - BUTTON_WIDTH / 2, BUTTON_OFFSETX, BUTTON_WIDTH, BUTTON_HEIGHT, TRUE);
	GetDlgItem(IDC_CANCELBUTTON)->MoveWindow(DIALOG_WIDTH / 3 * 2 - BUTTON_WIDTH / 2, BUTTON_OFFSETX, BUTTON_WIDTH, BUTTON_HEIGHT, TRUE);

	CSELECTION::updatePreview(_T("0"));
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
	/*
	// TEST
	CFileFind tempFind;
	BOOL IsFind = tempFind.FindFile(_T("/*.*"));
	MessageBox(_T(""), _T("From xht"));
	while (IsFind)
	{
		IsFind = tempFind.FindNextFile(); // 找到最后一个文件时返回FALSE
		if (tempFind.IsDots())
		{
			continue;
		}
		CString filename = tempFind.GetFileName();
		MessageBox(filename, _T("From xht"));
	}
	*/
	CString tempStr;;
	int ID = GetDlgItemText(IDC_IDINPUT, tempStr);
	tempStr = mapPath + _T("map") + tempStr + _T(".map");
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
		case VK_RETURN:
			HWND hwnd1 = ((CEdit*)GetDlgItem(IDC_IDINPUT))->m_hWnd;
			if (pMsg->hwnd == hwnd1)
			{
				OnBnClickedConfirmbutton();
				return TRUE;
			}
			break;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}

void CSELECTION::updatePreview(CString name) // 显示mapname的缩略图
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
	GetClientRect(tempRect);
	const int PREVIEW_OFFSETX = 180;
	pic->MoveWindow((tempRect.Width() - tempWidth) / 2, PREVIEW_OFFSETX, tempWidth, tempHeight, TRUE);
	pic->ShowWindow(SW_SHOW);
}
/*
xht:
picturecontrol是会随图片改变大小的，要读图，就要隐藏、重定位后再显现，不然炸图。
*/