#pragma once

#include "CGAME_Display.h"
#include "CGAME_Map.h"
#include "CRESOURCE.h"

/*
#define DIR_UP 0
#define DIR_DOWN 1
#define DIR_LEFT 2
#define DIR_RIGHT 3
#define DIR_FIRST 0
#define DIR_LAST 3

const int dx[4] = { -1, 1, 0, 0 };
const int dy[4] = { 0, 0, -1, 1 };
*/

// CGAME 对话框

class CGAME : public CDialogEx
{
	DECLARE_DYNAMIC(CGAME)

public:
	CGAME(CRESOURCE* currentRes, CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CGAME();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAME };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnTimer(UINT_PTR nIdEvent);
	virtual BOOL OnInitDialog();
	virtual BOOL DestroyWindow();
	afx_msg void OnBnClickedGameRestartbutton();
	afx_msg void OnBnClickedGameReturnbutton();
	afx_msg LRESULT StartGame(WPARAM wParam, LPARAM lParam);
protected:
	/*初始化计步器和计时器*/
	virtual void InitStepAndTimer();
	/*步数加一并更新步数显示*/
	virtual void IncrementStep(BOOL moved);
private:
	CFont m_font;
	int m_step,m_mm,m_ss;
	UINT_PTR m_Timer;
	CGAME_Display* myDisplay;
	CGAME_Map* myMap;
	CRESOURCE* myRes;
public:
	
};
