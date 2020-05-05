#pragma once

#include "CEDITOR_Display.h"
#include "CEDITOR_Map.h"

// CEDITOR dialog

class CEDITOR : public CDialogEx
{
	DECLARE_DYNAMIC(CEDITOR)

public:
	CEDITOR(CRESOURCE* currentRes, CWnd* pParent = nullptr);   // standard constructor
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
	CRESOURCE* myRes;
	CString m_filePath;
	/*mode{-1:没有打开的地图;0:编辑地图元素中;1:编辑人物位置中}*/
	int m_mode;
public:
	virtual BOOL DestroyWindow();
	afx_msg void OnBnClickedEditorReturnbutton();
	afx_msg void OnBnClickedEditorNewbutton();
	afx_msg void OnBnClickedEditorOpenbutton();
	afx_msg void OnBnClickedEditorSavebutton();
	afx_msg void OnBnClickedEditorSaveasbutton();
	afx_msg void OnBnClickedEditorClosebutton();
	afx_msg void OnBnClickedEditorUndobutton();
	afx_msg void OnBnClickedEditorRedobutton();
	afx_msg void OnBnClickedEditorSwitchbutton();
	virtual int QuerySave();
	virtual void Clear();
	/*根据MyMap是否可以撤销重做更新按钮*/
	virtual void UpdateUndoRedoButton();
};
