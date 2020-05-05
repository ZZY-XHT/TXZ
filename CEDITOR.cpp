// CEDITOR.cpp : implementation file
//

#include "pch.h"
#include "TXZ.h"
#include "CEDITOR.h"
#include "afxdialogex.h"
#include "CNEWMAP.h"

// CEDITOR dialog

IMPLEMENT_DYNAMIC(CEDITOR, CDialogEx)

CEDITOR::CEDITOR(CRESOURCE* currentRes, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_EDITOR, pParent),
	myDisplay(NULL), myMap(NULL), myRes(currentRes),
	m_filePath(_T("")), m_mode(-1)
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

	GetDlgItem(IDC_EDITOR_UNDOBUTTON)->MoveWindow(0, DIALOG_HEIGHT - BUTTON_HEIGHT, BUTTON_WIDTH, BUTTON_HEIGHT, TRUE);
	GetDlgItem(IDC_EDITOR_REDOBUTTON)->MoveWindow(BUTTON_WIDTH, DIALOG_HEIGHT - BUTTON_HEIGHT, BUTTON_WIDTH, BUTTON_HEIGHT, TRUE);
	GetDlgItem(IDC_EDITOR_SWITCHBUTTON)->MoveWindow(2 * BUTTON_WIDTH, DIALOG_HEIGHT - BUTTON_HEIGHT, 2 * BUTTON_WIDTH, BUTTON_HEIGHT, TRUE);
	GetDlgItem(IDC_EDITOR_CLOSEBUTTON)->MoveWindow(4 * BUTTON_WIDTH, DIALOG_HEIGHT - BUTTON_HEIGHT, BUTTON_WIDTH, BUTTON_HEIGHT, TRUE);

	// 创建Display
	myDisplay = new CEDITOR_Display(CRect(0, (int)(DIALOG_HEIGHT * 0.1), DIALOG_WIDTH, (int)(DIALOG_HEIGHT * 0.9)), myRes);
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
	GetDlgItem(IDC_EDITOR_UNDOBUTTON)->SetFont(&m_font);
	GetDlgItem(IDC_EDITOR_UNDOBUTTON)->SetWindowText(_T("撤销"));
	GetDlgItem(IDC_EDITOR_REDOBUTTON)->SetFont(&m_font);
	GetDlgItem(IDC_EDITOR_REDOBUTTON)->SetWindowText(_T("重做"));
	GetDlgItem(IDC_EDITOR_SWITCHBUTTON)->SetFont(&m_font);
	GetDlgItem(IDC_EDITOR_SWITCHBUTTON)->SetWindowText(_T("编辑人物位置"));
	GetDlgItem(IDC_EDITOR_CLOSEBUTTON)->SetFont(&m_font);
	GetDlgItem(IDC_EDITOR_CLOSEBUTTON)->SetWindowText(_T("关闭"));

	GetDlgItem(IDC_EDITOR_NEWBUTTON)->ShowWindow(TRUE);
	GetDlgItem(IDC_EDITOR_OPENBUTTON)->ShowWindow(TRUE);
	GetDlgItem(IDC_EDITOR_SAVEBUTTON)->ShowWindow(TRUE);
	GetDlgItem(IDC_EDITOR_SAVEASBUTTON)->ShowWindow(TRUE);
	GetDlgItem(IDC_EDITOR_RETURNBUTTON)->ShowWindow(TRUE);
	GetDlgItem(IDC_EDITOR_UNDOBUTTON)->ShowWindow(TRUE);
	GetDlgItem(IDC_EDITOR_REDOBUTTON)->ShowWindow(TRUE);
	GetDlgItem(IDC_EDITOR_SWITCHBUTTON)->ShowWindow(TRUE);
	GetDlgItem(IDC_EDITOR_CLOSEBUTTON)->ShowWindow(TRUE);

	GetDlgItem(IDC_EDITOR_SAVEBUTTON)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDITOR_SAVEASBUTTON)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDITOR_UNDOBUTTON)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDITOR_REDOBUTTON)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDITOR_SWITCHBUTTON)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDITOR_CLOSEBUTTON)->EnableWindow(FALSE);

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
		if (m_mode == 0 && GetAsyncKeyState(VK_CONTROL) & 0x8000)
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
		if (m_mode == 0)
		{
			myMap->Change(myDisplay->GetLastClicked());
			UpdateUndoRedoButton();
		}
		else if(m_mode == 1)
			myMap->ChangePlayer(myDisplay->GetLastClicked());
		return TRUE;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


BEGIN_MESSAGE_MAP(CEDITOR, CDialogEx)
	ON_BN_CLICKED(IDC_EDITOR_RETURNBUTTON, &CEDITOR::OnBnClickedEditorReturnbutton)
	ON_BN_CLICKED(IDC_EDITOR_NEWBUTTON, &CEDITOR::OnBnClickedEditorNewbutton)
	ON_BN_CLICKED(IDC_EDITOR_OPENBUTTON, &CEDITOR::OnBnClickedEditorOpenbutton)
	ON_BN_CLICKED(IDC_EDITOR_SAVEBUTTON, &CEDITOR::OnBnClickedEditorSavebutton)
	ON_BN_CLICKED(IDC_EDITOR_SAVEASBUTTON, &CEDITOR::OnBnClickedEditorSaveasbutton)
	ON_BN_CLICKED(IDC_EDITOR_CLOSEBUTTON, &CEDITOR::OnBnClickedEditorClosebutton)
	ON_BN_CLICKED(IDC_EDITOR_UNDOBUTTON, &CEDITOR::OnBnClickedEditorUndobutton)
	ON_BN_CLICKED(IDC_EDITOR_REDOBUTTON, &CEDITOR::OnBnClickedEditorRedobutton)
	ON_BN_CLICKED(IDC_EDITOR_SWITCHBUTTON, &CEDITOR::OnBnClickedEditorSwitchbutton)
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
	if (m_mode != -1)
	{
		if (QuerySave() == IDCANCEL) return;
	}
	Clear();
	GetParent()->PostMessage(WM_TOHOMEPAGE);
}

void CEDITOR::OnBnClickedEditorNewbutton()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_mode != -1)
	{
		if (QuerySave() == IDCANCEL) return;
	}

	CNEWMAP myDlg;
	if (myDlg.DoModal() == IDOK)
	{
		myMap->NewMap(myDlg.getRow(), myDlg.getColumn());
		m_filePath = _T("");
		m_mode = 1;
		GetDlgItem(IDC_EDITOR_SWITCHBUTTON)->SetWindowText(_T("编辑地图元素"));

		GetDlgItem(IDC_EDITOR_SAVEBUTTON)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDITOR_SAVEASBUTTON)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDITOR_SWITCHBUTTON)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDITOR_CLOSEBUTTON)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDITOR_UNDOBUTTON)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDITOR_REDOBUTTON)->EnableWindow(FALSE);

	}
}


void CEDITOR::OnBnClickedEditorOpenbutton()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_mode != -1)
	{
		if (QuerySave() == IDCANCEL) return;
	}

	CString filter;
	filter = _T("地图文件(*.txm)|*.txm||");
	CFileDialog openFileDlg(TRUE, NULL, NULL, OFN_NOCHANGEDIR | OFN_HIDEREADONLY | OFN_PATHMUSTEXIST, filter);
	openFileDlg.GetOFN().lpstrInitialDir = mapPath;
	if (openFileDlg.DoModal() == IDOK)
	{
		CString filepath = openFileDlg.GetPathName();
		if (myMap->SetMap(filepath, FALSE))
		{
			m_filePath = filepath;
			m_mode = 1;
			GetDlgItem(IDC_EDITOR_SWITCHBUTTON)->SetWindowText(_T("编辑地图元素"));

			GetDlgItem(IDC_EDITOR_SAVEBUTTON)->EnableWindow(TRUE);
			GetDlgItem(IDC_EDITOR_SAVEASBUTTON)->EnableWindow(TRUE);
			GetDlgItem(IDC_EDITOR_SWITCHBUTTON)->EnableWindow(TRUE);
			GetDlgItem(IDC_EDITOR_CLOSEBUTTON)->EnableWindow(TRUE);
			GetDlgItem(IDC_EDITOR_UNDOBUTTON)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDITOR_REDOBUTTON)->EnableWindow(FALSE);

		}
#ifdef MYDEBUG
		MessageBox(_T("666"), _T("From xht"));
#endif // MYDEBUG
	}
}


void CEDITOR::OnBnClickedEditorSavebutton()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_filePath == _T(""))
	{
		OnBnClickedEditorSaveasbutton();
	}
	else
	{
		if (myMap->WriteMap(m_filePath) == FALSE)
		{
			OnBnClickedEditorSaveasbutton();
		}
	}
}


void CEDITOR::OnBnClickedEditorSaveasbutton()
{
	// TODO: 在此添加控件通知处理程序代码
	CString filter;
	filter = _T("地图文件(*.txm)|*.txm||");
	CFileDialog openFileDlg(FALSE, NULL, NULL, OFN_HIDEREADONLY | OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT, filter);
	if (openFileDlg.DoModal() == IDOK)
	{
		CString filepath = openFileDlg.GetPathName();
		if (filepath.GetLength() < 4 || filepath.Right(4).CompareNoCase(_T(".txm")) != 0)
			filepath += _T(".txm");
		if (myMap->WriteMap(filepath))
		{
			m_filePath = filepath;
		}
#ifdef MYDEBUG
		MessageBox(_T("777"), _T("From xht"));
#endif // MYDEBUG
	}
}


void CEDITOR::OnBnClickedEditorClosebutton()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_mode != -1)
	{
		if (QuerySave() == IDCANCEL) return;
	}

	Clear();
}


void CEDITOR::OnBnClickedEditorUndobutton()
{
	// TODO: 在此添加控件通知处理程序代码
	myMap->Undo();
	UpdateUndoRedoButton();
}


void CEDITOR::OnBnClickedEditorRedobutton()
{
	// TODO: 在此添加控件通知处理程序代码
	myMap->Redo();
	UpdateUndoRedoButton();
}


void CEDITOR::OnBnClickedEditorSwitchbutton()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_mode == 0)
	{
		m_mode = 1;
		myMap->ShowPlayer();
		GetDlgItem(IDC_EDITOR_SWITCHBUTTON)->SetWindowText(_T("编辑地图元素"));
		GetDlgItem(IDC_EDITOR_UNDOBUTTON)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDITOR_REDOBUTTON)->EnableWindow(FALSE);
	}
	else if(m_mode == 1)
	{
		m_mode = 0;
		myMap->HidePlayer();
		GetDlgItem(IDC_EDITOR_SWITCHBUTTON)->SetWindowText(_T("编辑人物位置"));
		//GetDlgItem(IDC_EDITOR_UNDOBUTTON)->EnableWindow(TRUE);
		//GetDlgItem(IDC_EDITOR_REDOBUTTON)->EnableWindow(TRUE);
		UpdateUndoRedoButton();
	}
}

int CEDITOR::QuerySave()
{
	if (myMap->Modified())
	{
		int res = MessageBox(_T("是否要保存对当前地图的更改？"), _T("From xht"), MB_YESNOCANCEL);
		if (res == IDYES) OnBnClickedEditorSavebutton();
		return res;
	}
	else
	{
		return IDYES;
	}
}

void CEDITOR::Clear()
{
	m_mode = -1;
	myDisplay->Clear(TRUE);
	m_filePath = _T("");
	GetDlgItem(IDC_EDITOR_SAVEBUTTON)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDITOR_SAVEASBUTTON)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDITOR_UNDOBUTTON)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDITOR_REDOBUTTON)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDITOR_SWITCHBUTTON)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDITOR_CLOSEBUTTON)->EnableWindow(FALSE);
}

void CEDITOR::UpdateUndoRedoButton()
{
	assert(m_mode == 0);
	GetDlgItem(IDC_EDITOR_UNDOBUTTON)->EnableWindow(myMap->CanUndo());
	GetDlgItem(IDC_EDITOR_REDOBUTTON)->EnableWindow(myMap->CanRedo());
}