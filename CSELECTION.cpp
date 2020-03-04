// CSELECTION.cpp: 实现文件
//

#include "pch.h"
#include "TXZ.h"
#include "CSELECTION.h"
#include "afxdialogex.h"


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
	ON_BN_CLICKED(IDC_CANCEL, &CSELECTION::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_OK, &CSELECTION::OnBnClickedOk)
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

	// 设置窗口按钮和文本
	/*
	字体、文字大小、文字内容
	按钮和文本大小、按钮和文本位置
	焦点位置
	*/

	// 字体、文字大小、文字内容
	CFont* f;
	f = new CFont;
	f->CreateFont(
		32, // nHeight 
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
	GetDlgItem(IDC_CANCEL)->SetFont(f);
	GetDlgItem(IDC_CANCEL)->SetWindowText(_T("返回"));
	GetDlgItem(IDC_OK)->SetFont(f);
	GetDlgItem(IDC_OK)->SetWindowText(_T("确认"));
	GetDlgItem(IDC_TEXT1)->SetFont(f);
	GetDlgItem(IDC_TEXT1)->SetWindowText(_T("请输入关卡编号："));

	GetDlgItem(IDC_IDINPUT)->SetFont(f);
	GetDlgItem(IDC_IDINPUT)->SetWindowText(_T("0"));
	CSELECTION::updatePreview(_T("1"));//MYSHIT
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CSELECTION::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	GetParent()->PostMessage(WM_TOHOMEPAGE);
}


void CSELECTION::OnBnClickedOk()
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
			OnBnClickedCancel();
			return TRUE;
			break;
		case VK_RETURN:
			HWND hwnd1 = ((CEdit*)GetDlgItem(IDC_IDINPUT))->m_hWnd;
			if (pMsg->hwnd == hwnd1)
			{
				OnBnClickedOk();
				return TRUE;
			}
			break;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}

void CSELECTION::updatePreview(CString name)//显示mapname的缩略图
{
	CStatic* pic=(CStatic*)GetDlgItem(IDC_STATIC);//预览图的控件
	CString previewImageDir;//位图位置
	HBITMAP hBMP;//载入的bmp

	name = "0";
	previewImageDir = mapPath + _T("map") + name + _T(".bmp");
	hBMP = (HBITMAP)LoadImage(NULL, previewImageDir, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	
	if (hBMP == NULL) {
		//没有缩略图就显示一个默认的defaultmap.bmp
		previewImageDir = mapPath + _T("defaultmap.bmp");
		hBMP = (HBITMAP)LoadImage(NULL, previewImageDir, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	}

	pic->SetBitmap(hBMP);
	
	

}