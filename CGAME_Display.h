#pragma once
#include "CBASE_Display.h"
class CGAME_Display :
	public CBASE_Display
{
public:
	CGAME_Display(CRect area, CRESOURCE* currentRes, CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CGAME_Display();
};