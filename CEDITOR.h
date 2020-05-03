#pragma once

#include "CEDITOR_Display.h"
#include "CEDITOR_Map.h"

// CEDITOR dialog

class CEDITOR : public CDialogEx
{
	DECLARE_DYNAMIC(CEDITOR)

public:
	CEDITOR(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CEDITOR();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EDITOR };
#endif

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	DECLARE_MESSAGE_MAP()
private:
	CFont m_font;
	CEDITOR_Display* myDisplay;
	CEDITOR_Map* myMap;
public:
	virtual BOOL DestroyWindow();
	afx_msg void OnBnClickedEditorReturnbutton();
	afx_msg void OnBnClickedEditorNewbutton();
	afx_msg void OnBnClickedEditorOpenbutton();
};
