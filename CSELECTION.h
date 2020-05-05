#pragma once
#include "CBASE_Map.h"
#include "CRESOURCE.h"

// CSELECTION 对话框

class CSELECTION : public CDialogEx
{
	DECLARE_DYNAMIC(CSELECTION)

public:
	CSELECTION(CRESOURCE* currentRes, CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CSELECTION();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SELECTION };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedSelectionConfirmbutton();
	afx_msg void OnBnClickedSelectionCancelbutton();
	virtual void UpdatePreview(CString name);
	virtual void InitList();
private:
	CFont m_buttonFont, m_listFont;
	CBASE_Map* myMap;
	CBASE_Display* myDisplay;
	CRESOURCE* myRes;
public:
	afx_msg void OnLbnSelchangeSelectionMaplist();
};
