#pragma once


// CSELECTION 对话框

class CSELECTION : public CDialogEx
{
	DECLARE_DYNAMIC(CSELECTION)

public:
	CSELECTION(CWnd* pParent = nullptr);   // 标准构造函数
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
	afx_msg void OnBnClickedConfirmbutton();
	afx_msg void OnBnClickedCancelbutton();
	virtual void updatePreview(CString name);
private:
	CFont m_font;
};
