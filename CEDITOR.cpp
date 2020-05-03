// CEDITOR.cpp : implementation file
//

#include "pch.h"
#include "TXZ.h"
#include "CEDITOR.h"
#include "afxdialogex.h"
#include "CNEWMAP.h"

// CEDITOR dialog

IMPLEMENT_DYNAMIC(CEDITOR, CDialogEx)

CEDITOR::CEDITOR(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_EDITOR, pParent),
	myDisplay(NULL), myMap(NULL)
{

}

CEDITOR::~CEDITOR()
{
}

BOOL CEDITOR::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CRect ClientRect;
	GetParent()->GetClientRect(ClientRect);
	MoveWindow(ClientRect);
	const int DIALOG_HEIGHT = ClientRect.Height();
	const int DIALOG_WIDTH = ClientRect.Width();

	this->SetBackgroundColor(RGB(255, 0, 255), TRUE);
	// 设置控件大小、位置
	const int BUTTON_HEIGHT = (int)(DIALOG_HEIGHT * 0.1);
	const int BUTTON_WIDTH = BUTTON_HEIGHT * 2;
	GetDlgItem(IDC_EDITOR_NEWBUTTON)->MoveWindow(0, 0, BUTTON_WIDTH, BUTTON_HEIGHT, TRUE);
	GetDlgItem(IDC_EDITOR_OPENBUTTON)->MoveWindow(BUTTON_WIDTH, 0, BUTTON_WIDTH, BUTTON_HEIGHT, TRUE);
	GetDlgItem(IDC_EDITOR_SAVEBUTTON)->MoveWindow(2 * BUTTON_WIDTH, 0, BUTTON_WIDTH, BUTTON_HEIGHT, TRUE);
	GetDlgItem(IDC_EDITOR_SAVEASBUTTON)->MoveWindow(3 * BUTTON_WIDTH, 0, BUTTON_WIDTH, BUTTON_HEIGHT, TRUE);
	GetDlgItem(IDC_EDITOR_RETURNBUTTON)->MoveWindow(4 * BUTTON_WIDTH, 0, BUTTON_WIDTH, BUTTON_HEIGHT, TRUE);

	// 创建Display
	myDisplay = new CEDITOR_Display(CRect(0, (int)(DIALOG_HEIGHT * 0.1), DIALOG_WIDTH, (int)(DIALOG_HEIGHT * 0.9)));
	myDisplay->Create(IDD_DISPLAY, this);

	// 创建Map
	myMap = new CEDITOR_Map(myDisplay);

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
	GetDlgItem(IDC_EDITOR_NEWBUTTON)->SetFont(&m_font);
	GetDlgItem(IDC_EDITOR_NEWBUTTON)->SetWindowText(_T("新建"));
	GetDlgItem(IDC_EDITOR_OPENBUTTON)->SetFont(&m_font);
	GetDlgItem(IDC_EDITOR_OPENBUTTON)->SetWindowText(_T("打开"));
	GetDlgItem(IDC_EDITOR_SAVEBUTTON)->SetFont(&m_font);
	GetDlgItem(IDC_EDITOR_SAVEBUTTON)->SetWindowText(_T("保存"));
	GetDlgItem(IDC_EDITOR_SAVEASBUTTON)->SetFont(&m_font);
	GetDlgItem(IDC_EDITOR_SAVEASBUTTON)->SetWindowText(_T("另存为"));
	GetDlgItem(IDC_EDITOR_RETURNBUTTON)->SetFont(&m_font);
	GetDlgItem(IDC_EDITOR_RETURNBUTTON)->SetWindowText(_T("返回"));

	GetDlgItem(IDC_EDITOR_NEWBUTTON)->ShowWindow(TRUE);
	GetDlgItem(IDC_EDITOR_OPENBUTTON)->ShowWindow(TRUE);
	GetDlgItem(IDC_EDITOR_SAVEBUTTON)->ShowWindow(TRUE);
	GetDlgItem(IDC_EDITOR_SAVEASBUTTON)->ShowWindow(TRUE);
	GetDlgItem(IDC_EDITOR_RETURNBUTTON)->ShowWindow(TRUE);

	// myMap->NewMap(3, 3);
	return TRUE;
}

void CEDITOR::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BOOL CEDITOR::PreTranslateMessage(MSG* pMsg)
{
	switch (pMsg->message)
	{
	case WM_KEYDOWN:
		if (GetAsyncKeyState(VK_CONTROL) & 0x8000)
			switch (pMsg->wParam)
			{
			case 'Z':
				myMap->Undo();
				return TRUE;
			case 'Y':
				myMap->Redo();
				return TRUE;
			}
		switch (pMsg->wParam)
		{
		case VK_ESCAPE:
			OnBnClickedEditorReturnbutton();
			break;
		}
		break;

	case WM_EDITORMAPCLICKED:
		myMap->Change(myDisplay->GetLastClicked());
		return TRUE;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


BEGIN_MESSAGE_MAP(CEDITOR, CDialogEx)
	ON_BN_CLICKED(IDC_EDITOR_RETURNBUTTON, &CEDITOR::OnBnClickedEditorReturnbutton)
	ON_BN_CLICKED(IDC_EDITOR_NEWBUTTON, &CEDITOR::OnBnClickedEditorNewbutton)
	ON_BN_CLICKED(IDC_EDITOR_OPENBUTTON, &CEDITOR::OnBnClickedEditorOpenbutton)
END_MESSAGE_MAP()

// CEDITOR message handlers

BOOL CEDITOR::DestroyWindow()
{
	// TODO: 在此添加专用代码和/或调用基类
	myDisplay->DestroyWindow();
	delete myDisplay;
	delete myMap;

	return CDialogEx::DestroyWindow();
}

void CEDITOR::OnBnClickedEditorReturnbutton()
{
	// TODO: 在此添加控件通知处理程序代码
	myDisplay->Clear();
	GetParent()->PostMessage(WM_TOHOMEPAGE);
}


void CEDITOR::OnBnClickedEditorNewbutton()
{
	// TODO: 在此添加控件通知处理程序代码
	CNEWMAP myDlg;
	myDlg.DoModal();

}


void CEDITOR::OnBnClickedEditorOpenbutton()
{
	// TODO: 在此添加控件通知处理程序代码
	CString filter;
	filter = _T("地图文件(*.txm)|*.txm||");
	CFileDialog openFileDlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_PATHMUSTEXIST, filter);
	if (openFileDlg.DoModal() == IDOK)
	{
		CString filepath = openFileDlg.GetPathName();
		myMap->SetMap(filepath);
		MessageBox(_T("666"), _T("From xht"));
	}
}
