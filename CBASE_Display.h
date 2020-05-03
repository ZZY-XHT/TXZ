#pragma once
#include "CRESOURCE.h"

// CBASE_Display 对话框

class CBASE_Display : public CDialogEx
{
	DECLARE_DYNAMIC(CBASE_Display)

public:
	CBASE_Display(CRect area, CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CBASE_Display();

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
	/*清理释放内存空间*/
	virtual void Clear();
	/*在显示区域居中重绘n*m的方格*/
	virtual BOOL Reset(int n, int m);
	/*更新格子(x,y)的图片显示*/
	virtual void Update(int x, int y, UINT picTag, bool singleUpdate = TRUE);
protected:
	CRESOURCE* myRes;
	int m_size;
	CRect m_area;
	CStatic* m_pPictureMap[MAXMAPSIZE + 2][MAXMAPSIZE + 2];
	//CBitmap m_bitmap[PICNUM];
};