#pragma once
#include "CBASE_Display.h"
class CEDITOR_Display :
	public CBASE_Display
{
public:
	CEDITOR_Display(CRect area, CRESOURCE* currentRes, CWnd* pParent = nullptr);   // ��׼���캯��
	virtual ~CEDITOR_Display();
public:
	//����1024*r+c
	virtual int GetLastClicked();
private:
	int m_lastClickedR, m_lastClickedC;
protected:
	/*�����������ĸ�ͼƬ������*/
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};