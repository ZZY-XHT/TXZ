// CNEWMAP.cpp: 实现文件
//

#include "pch.h"
#include "TXZ.h"
#include "CNEWMAP.h"
#include "afxdialogex.h"


// CNEWMAP 对话框

IMPLEMENT_DYNAMIC(CNEWMAP, CDialogEx)

CNEWMAP::CNEWMAP(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_NEWMAP, pParent)
{

}

CNEWMAP::~CNEWMAP()
{
}

void CNEWMAP::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CNEWMAP, CDialogEx)
END_MESSAGE_MAP()


// CNEWMAP 消息处理程序
