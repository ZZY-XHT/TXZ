﻿#pragma once


// CHOMEPAGE 对话框

class CHOMEPAGE : public CDialogEx
{
	DECLARE_DYNAMIC(CHOMEPAGE)

public:
	CHOMEPAGE(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CHOMEPAGE();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HOMEPAGE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedStartgame();
	afx_msg void OnBnClickedExitgame();
	afx_msg void OnBnClickedEditmap();
private:
	CFont m_font;
};
