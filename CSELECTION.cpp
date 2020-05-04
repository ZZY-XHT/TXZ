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
	ON_BN_CLICKED(IDC_SELECTION_CONFIRMBUTTON, &CSELECTION::OnBnClickedSelectionConfirmbutton)
	ON_BN_CLICKED(IDC_SELECTION_CANCELBUTTON, &CSELECTION::OnBnClickedSelectionCancelbutton)
	ON_LBN_SELCHANGE(IDC_SELECTION_MAPLIST, &CSELECTION::OnLbnSelchangeSelectionMaplist)
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
	GetDlgItem(IDC_SELECTION_CONFIRMBUTTON)->MoveWindow((int)(DIALOG_WIDTH * 0.55), (int)(DIALOG_HEIGHT * 0.6), BUTTON_WIDTH, BUTTON_HEIGHT);
	GetDlgItem(IDC_SELECTION_CANCELBUTTON)->MoveWindow((int)(DIALOG_WIDTH * 0.55), (int)(DIALOG_HEIGHT * 0.75), BUTTON_WIDTH, BUTTON_HEIGHT);

	const int LIST_HEIGHT = (int)(DIALOG_HEIGHT * 0.7);
	const int LIST_WIDTH = (int)(DIALOG_WIDTH * 0.45);
	GetDlgItem(IDC_SELECTION_MAPLIST)->MoveWindow((int)(DIALOG_WIDTH * 0.05), (int)(DIALOG_HEIGHT * 0.05), LIST_WIDTH, LIST_HEIGHT);

	// 开始创建动态预览图
	myDisplay = new CBASE_Display(CRect((int)(DIALOG_WIDTH * 0.55), (int)(DIALOG_HEIGHT * 0.1), (int)(DIALOG_WIDTH * 0.95), (int)(DIALOG_HEIGHT*0.6)));
	myDisplay->Create(IDD_DISPLAY, this);

	// 创建Map
	myMap = new CBASE_Map(myDisplay,false);

	// 失败图片
	CStatic* pic = (CStatic*)GetDlgItem(IDC_SELECTION_PREVIEWIMAGE);
	CString failBMP;
	HBITMAP hBMP; // 载入的bmp
	//TODO: 把这个加入CRESOURCE，然后把MyRes弄成全局的
	failBMP = _T("./Resource/P_preview_fail.bmp");
	hBMP = (HBITMAP)LoadImage(NULL, failBMP, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	pic->ShowWindow(SW_HIDE);
	pic->SetBitmap(hBMP);
	pic->MoveWindow((int)(DIALOG_WIDTH * 0.55), (int)(DIALOG_HEIGHT * 0.05), (int)(DIALOG_WIDTH * 0.4), (int)(DIALOG_HEIGHT * 0.45));

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
	GetDlgItem(IDC_SELECTION_CANCELBUTTON)->SetFont(&m_buttonFont);
	GetDlgItem(IDC_SELECTION_CANCELBUTTON)->SetWindowText(_T("返回"));
	GetDlgItem(IDC_SELECTION_CANCELBUTTON)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_SELECTION_CONFIRMBUTTON)->SetFont(&m_buttonFont);
	GetDlgItem(IDC_SELECTION_CONFIRMBUTTON)->SetWindowText(_T("确认"));
	GetDlgItem(IDC_SELECTION_CONFIRMBUTTON)->ShowWindow(SW_SHOW);
	

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
	GetDlgItem(IDC_SELECTION_MAPLIST)->SetFont(&m_listFont);
	
	InitList();
	GetDlgItem(IDC_SELECTION_MAPLIST)->ShowWindow(SW_SHOW);


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CSELECTION::OnBnClickedSelectionCancelbutton()
{
	// TODO: 在此添加控件通知处理程序代码
	GetParent()->PostMessage(WM_TOHOMEPAGE);
}


void CSELECTION::OnBnClickedSelectionConfirmbutton()
{
	// TODO: 在此添加控件通知处理程序代码
	CListBox* myList = (CListBox*)GetDlgItem(IDC_SELECTION_MAPLIST);
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
			OnBnClickedSelectionCancelbutton();
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

void CSELECTION::UpdatePreview(CString mapName) // 显示mapName的缩略图
{
	CStatic* pic = (CStatic*)GetDlgItem(IDC_SELECTION_PREVIEWIMAGE); // 预览图的控件

	CString selectedMapDir;
	selectedMapDir = mapPath + mapName + _T(".txm");
	myDisplay->ShowWindow(SW_HIDE);
	if (myMap->SetMap(selectedMapDir))
	{
		myDisplay->ShowWindow(SW_SHOW);
		pic->ShowWindow(SW_HIDE);
	}
	else
	{
		pic->ShowWindow(SW_SHOW);
	}
	/*
	CStatic* pic = (CStatic*)GetDlgItem(IDC_SELECTION_PREVIEWIMAGE); // 预览图的控件
	pic->ShowWindow(SW_HIDE);

	CString previewImageDir; // 位图位置
	HBITMAP hBMP; // 载入的bmp

	previewImageDir = mapPath + mapName + _T(".bmp");
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
	*/
}

void CSELECTION::InitList()
{
	CFileFind tempFind;
	BOOL IsFind = tempFind.FindFile(mapPath + _T("/*.txm"));
	CListBox* myList = (CListBox*)GetDlgItem(IDC_SELECTION_MAPLIST);

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
		OnLbnSelchangeSelectionMaplist();
		GetDlgItem(IDC_SELECTION_CONFIRMBUTTON)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_SELECTION_CONFIRMBUTTON)->EnableWindow(FALSE);
	}
}

void CSELECTION::OnLbnSelchangeSelectionMaplist()
{
	// TODO: 在此添加控件通知处理程序代码
	CListBox* myList = (CListBox*)GetDlgItem(IDC_SELECTION_MAPLIST);
	CString tempStr;
	myList->GetText(myList->GetCurSel(), tempStr);
	UpdatePreview(tempStr);
}
