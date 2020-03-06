#pragma once


// CDisplay 对话框

class CDisplay : public CDialogEx
{
	DECLARE_DYNAMIC(CDisplay)

public:
	CDisplay(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDisplay();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DISPLAY };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL DestroyWindow();
	virtual void Clear();
	virtual BOOL Reset(int n, int m);
	virtual void Update(int x, int y, UINT picTag);
private:
	int m_size, m_offsetX, m_offsetY;
	CStatic* m_pPictureMap[MAXMAPSIZE + 2][MAXMAPSIZE + 2];
	CBitmap m_bitmap[PICNUM];
};