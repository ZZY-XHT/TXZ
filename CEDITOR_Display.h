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
	/*在这里检查是哪个图片被按了*/
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};