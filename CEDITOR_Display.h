#pragma once
#include <utility>
#include "CGAME_Display.h"
class CEDITOR_Display :
	public CGAME_Display
{
public:
	CEDITOR_Display(CRect area, CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CEDITOR_Display();
protected:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};