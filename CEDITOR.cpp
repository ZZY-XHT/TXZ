// CEDITOR.cpp : implementation file
//

#include "pch.h"
#include "TXZ.h"
#include "CEDITOR.h"
#include "afxdialogex.h"


// CEDITOR dialog

IMPLEMENT_DYNAMIC(CEDITOR, CDialogEx)

CEDITOR::CEDITOR(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_EDITOR, pParent)
{

}

CEDITOR::~CEDITOR()
{
}

void CEDITOR::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
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

BEGIN_MESSAGE_MAP(CEDITOR, CDialogEx)
END_MESSAGE_MAP()


// CEDITOR message handlers
