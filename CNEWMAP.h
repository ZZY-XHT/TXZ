#pragma once


// CNEWMAP 对话框

class CNEWMAP : public CDialogEx
{
	DECLARE_DYNAMIC(CNEWMAP)

public:
	CNEWMAP(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CNEWMAP();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NEWMAP };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
