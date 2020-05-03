#include "pch.h"
#include "CEDITOR_Display.h"

CEDITOR_Display::CEDITOR_Display(CRect area, CWnd* pParent)
	:CBASE_Display(area, pParent),
	m_lastClickedR(-1), m_lastClickedC(-1)
{

}

CEDITOR_Display::~CEDITOR_Display()
{
}

BOOL CEDITOR_Display::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_LBUTTONDOWN)
	{
		CPoint mousePoint;
		GetCursorPos(&mousePoint);
		CRect displayRect;
		GetWindowRect(&displayRect);
		m_lastClickedC = (mousePoint.x - displayRect.left) / m_size + 1;
		m_lastClickedR = (mousePoint.y - displayRect.top) / m_size + 1;
		GetParent()->PostMessage(WM_EDITORMAPCLICKED);
	}
	return TRUE;
}

int CEDITOR_Display::GetLastClicked() {
	//这里可以写一些Check
	return m_lastClickedR * 1024 + m_lastClickedC;
}