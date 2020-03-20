#include "pch.h"
#include "CEDITOR_Display.h"

CEDITOR_Display::CEDITOR_Display(CRect area, CWnd* pParent)
	:CGAME_Display(area, pParent)
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
		this->GetWindowRect(&displayRect);
		int c = (mousePoint.x - displayRect.left) / m_size;
		int r = (mousePoint.y - displayRect.top) / m_size;
		CString str;
		str.Format(_T("%d %d"), r, c);
		MessageBox(str, _T("我被按了"));
		//然后Send一个Message给CEditor?
	}
	return TRUE;
}