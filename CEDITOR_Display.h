#pragma once
#include "CBASE_Display.h"
class CEDITOR_Display :
	public CBASE_Display
{
public:
	CEDITOR_Display(CRect area, CRESOURCE* currentRes, CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CEDITOR_Display();
public:
	//返回1024*r+c
	virtual int GetLastClicked();
private:
	int m_lastClickedR, m_lastClickedC;
protected:
	/*在这里检查是哪个图片被按了*/
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};