
// TXZDlg.h: 头文件
//
#include "CHOMEPAGE.h"
#include "CGAME.h"
#include "CSELECTION.h"
#include "CEDITOR.h"
#include "CRESOURCE.h"
#pragma once


// CTXZDlg 对话框
class CTXZDlg : public CDialogEx
{
// 构造
public:
	CTXZDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TXZ_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	virtual BOOL PreTranslateMessage(MSG* pMsg);
public:
	afx_msg LRESULT ToGame(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT ToHomepage(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT ToSelection(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT ToEditor(WPARAM wParam, LPARAM lParam);
	virtual BOOL DestroyWindow();
private:
	CHOMEPAGE* myHomepage;
	CGAME* myGame;
	CSELECTION* mySelection;
	CEDITOR* myEditor;
	CRESOURCE* myRes;
};
