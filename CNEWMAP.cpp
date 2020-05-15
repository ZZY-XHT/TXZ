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
	, m_row_str(_T(""))
	, m_column_str(_T(""))
{

}

CNEWMAP::~CNEWMAP()
{
}

void CNEWMAP::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_CBString(pDX, IDC_NEWMAP_ROW_COMBO, m_row_str);
	DDX_CBString(pDX, IDC_NEWMAP_COLUMN_COMBO, m_column_str);
}


BEGIN_MESSAGE_MAP(CNEWMAP, CDialogEx)
END_MESSAGE_MAP()


// CNEWMAP 消息处理程序

int CNEWMAP::getRow() const
{
	return _ttoi(m_row_str);
}

int CNEWMAP::getColumn() const
{
	return _ttoi(m_column_str);
}

BOOL CNEWMAP::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	// 实际大小 DIALOG_HEIGHT * DIALOG_WEIGHT
	const int DIALOG_HEIGHT = 300;
	const int DIALOG_WIDTH = 500;
	MoveWindow(0, 0, DIALOG_WIDTH, DIALOG_HEIGHT); // 初始大小
	CRect selfRect;
	this->GetClientRect(selfRect);
	MoveWindow(0, 0, DIALOG_WIDTH + DIALOG_WIDTH - selfRect.Width(), DIALOG_HEIGHT + DIALOG_HEIGHT - selfRect.Height()); // 修正大小
	CenterWindow(); // 居中

	this->SetBackgroundColor(RGB(255, 255, 0), TRUE);
	/*
	CString str;
	str.Format(_T("Height is %d, Weight is %d"), DIALOG_HEIGHT, DIALOG_WIDTH);
	MessageBox(str, _T("xht"));
	*/

	// 设置控件大小、位置
	const int BUTTON_HEIGHT = (int)(DIALOG_HEIGHT * 0.2);
	const int BUTTON_WIDTH = BUTTON_HEIGHT * 2;
	GetDlgItem(IDOK)->MoveWindow((int)(DIALOG_WIDTH * 0.2), (int)(DIALOG_HEIGHT * 0.6), BUTTON_WIDTH, BUTTON_HEIGHT, TRUE);
	GetDlgItem(IDCANCEL)->MoveWindow((int)(DIALOG_WIDTH * 0.8) - BUTTON_WIDTH, (int)(DIALOG_HEIGHT * 0.6), BUTTON_WIDTH, BUTTON_HEIGHT, TRUE);
	const int TEXT_HEIGHT = BUTTON_HEIGHT;
	const int TEXT_WIDTH = TEXT_HEIGHT;
	const int COMBO_HEIGHT = TEXT_HEIGHT;
	const int COMBO_WIDTH = (int)(COMBO_HEIGHT * 1.5);
	GetDlgItem(IDC_NEWMAP_ROW_STATIC)->MoveWindow((int)(DIALOG_WIDTH * 0.45) - COMBO_WIDTH - TEXT_WIDTH, (int)(DIALOG_HEIGHT * 0.2), TEXT_WIDTH, TEXT_HEIGHT, TRUE);
	GetDlgItem(IDC_NEWMAP_COLUMN_STATIC)->MoveWindow((int)(DIALOG_WIDTH * 0.55), (int)(DIALOG_HEIGHT * 0.2), TEXT_WIDTH, TEXT_HEIGHT, TRUE);
	GetDlgItem(IDC_NEWMAP_ROW_COMBO)->MoveWindow((int)(DIALOG_WIDTH * 0.45) - COMBO_WIDTH, (int)(DIALOG_HEIGHT * 0.2), COMBO_WIDTH, COMBO_HEIGHT, TRUE);
	GetDlgItem(IDC_NEWMAP_COLUMN_COMBO)->MoveWindow((int)(DIALOG_WIDTH * 0.55) + TEXT_WIDTH, (int)(DIALOG_HEIGHT * 0.2), COMBO_WIDTH, COMBO_HEIGHT, TRUE);

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
	GetDlgItem(IDOK)->SetFont(&m_font);
	GetDlgItem(IDOK)->SetWindowText(_T("确定"));
	GetDlgItem(IDCANCEL)->SetFont(&m_font);
	GetDlgItem(IDCANCEL)->SetWindowText(_T("取消"));
	GetDlgItem(IDC_NEWMAP_ROW_STATIC)->SetFont(&m_font);
	GetDlgItem(IDC_NEWMAP_ROW_STATIC)->SetWindowText(_T("行"));
	GetDlgItem(IDC_NEWMAP_COLUMN_STATIC)->SetFont(&m_font);
	GetDlgItem(IDC_NEWMAP_COLUMN_STATIC)->SetWindowText(_T("列"));
	GetDlgItem(IDC_NEWMAP_ROW_COMBO)->SetFont(&m_font);
	GetDlgItem(IDC_NEWMAP_COLUMN_COMBO)->SetFont(&m_font);

	m_row_str = _T("8");
	m_column_str = _T("8");
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
