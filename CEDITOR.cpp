// CEDITOR.cpp : implementation file
//

#include "pch.h"
#include "TXZ.h"
#include "CEDITOR.h"
#include "afxdialogex.h"


// CEDITOR dialog

IMPLEMENT_DYNAMIC(CEDITOR, CDialogEx)

CEDITOR::CEDITOR(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_EDITOR, pParent),
	myDisplay(NULL), myMap(NULL),
	m_ctrlDown(FALSE)
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

	myDisplay = new CEDITOR_Display(CRect(0, (int)(DIALOG_HEIGHT * 0.1), DIALOG_WIDTH, DIALOG_HEIGHT));
	myDisplay->Create(IDD_DISPLAY, this);
	myMap = new CEDITOR_Map(myDisplay);
	myMap->NewMap(3, 3);
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
		if (pMsg->wParam == VK_CONTROL)
		{
			m_ctrlDown = TRUE;
			return TRUE;
		}
		if (m_ctrlDown)
			switch (pMsg->wParam)
			{
			case 'Z':
				myMap->Undo();
				return TRUE;
			case 'R':
				myMap->Redo();
				return TRUE;
			}
	case WM_KEYUP:
		if (pMsg->wParam == VK_CONTROL) m_ctrlDown = FALSE;
		return TRUE;
	case WM_EDITORMAPCLICKED:
		myMap->Change(myDisplay->GetLastClicked());
		return TRUE;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


BEGIN_MESSAGE_MAP(CEDITOR, CDialogEx)
END_MESSAGE_MAP()

// CEDITOR message handlers

BOOL CEDITOR::DestroyWindow()
{
	// TODO: �ڴ�����ר�ô����/����û���
	myDisplay->DestroyWindow();
	delete myDisplay;
	delete myMap;

	return CDialogEx::DestroyWindow();
}