#pragma once
#include "CBASE_Display.h"
class CEDITOR_Display :
	public CBASE_Display
{
public:
	CEDITOR_Display(CRect area, CWnd* pParent = nullptr);   // ��׼���캯��
	virtual ~CEDITOR_Display();
public:
private:
protected:
	/*�����������ĸ�ͼƬ������*/
	virtual BOOL PreTranslateMessage(MSG* pMsg);
}; 