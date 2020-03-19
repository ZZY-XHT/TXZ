#include "CEDITOR_Display.h"
#include "CEDITOR_Map.h"
#pragma once


// CEDITOR dialog

class CEDITOR : public CDialogEx
{
	DECLARE_DYNAMIC(CEDITOR)

public:
	CEDITOR(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CEDITOR();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EDITOR };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
private:
	CEDITOR_Display* myDisplay;
	CEDITOR_Map* myMap;
};
