#pragma once
#include "CGAME_Display.h"
class CEDITOR_Display :
	public CGAME_Display
{
protected:
	DECLARE_MESSAGE_MAP()
public:
	CEDITOR_Display(CRect area, CWnd* pParent = nullptr);   // ��׼���캯��
	virtual ~CEDITOR_Display();
	afx_msg void OnPictureClick(UINT uID);
};