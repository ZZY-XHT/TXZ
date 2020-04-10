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
		break;
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
	// TODO: 在此添加专用代码和/或调用基类
	myDisplay->DestroyWindow();
	delete myDisplay;
	delete myMap;

	return CDialogEx::DestroyWindow();
}