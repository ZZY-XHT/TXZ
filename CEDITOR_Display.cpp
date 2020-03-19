#include "pch.h"
#include "CEDITOR_Display.h"

CEDITOR_Display::CEDITOR_Display(CRect area, CWnd* pParent)
	:CGAME_Display(area, pParent)
{

}

CEDITOR_Display::~CEDITOR_Display()
{
}

BEGIN_MESSAGE_MAP(CEDITOR_Display, CGAME_Display)
	ON_COMMAND_RANGE(IDC_D_BMP, IDC_D_BMP + (MAXMAPSIZE+2) * (MAXMAPSIZE+2) + 1, &CEDITOR_Display::OnPictureClick)
END_MESSAGE_MAP()

afx_msg void CEDITOR_Display::OnPictureClick(UINT uID)
{
	CString str;
	str.Format(_T("%d"), uID);
	MessageBox(str, _T("click"));
}