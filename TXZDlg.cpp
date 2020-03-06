
// TXZDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "TXZ.h"
#include "TXZDlg.h"
#include "afxdialogex.h"
#include "CHOMEPAGE.h"
#include "CGAME.h"
#include "CSELECTION.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CHOMEPAGE* myHomepage;
CGAME* myGame;
CSELECTION* mySelection;

CString mapPath;
CString resPath;
CString appPath;


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTXZDlg 对话框



CTXZDlg::CTXZDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TXZ_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTXZDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTXZDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_TOGAME, &ToGame)
	ON_MESSAGE(WM_TOHOMEPAGE, &ToHomepage)
	ON_MESSAGE(WM_TOSELECTION, &ToSelection)
END_MESSAGE_MAP()


// CTXZDlg 消息处理程序

BOOL CTXZDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	// 获取文件路径
	TCHAR myPath[MAX_PATH] = { 0 };
	GetModuleFileName(NULL, myPath, MAX_PATH);
	CString tempStr = myPath;
	tempStr = tempStr.Left(tempStr.ReverseFind('\\')) + _T("\\");
	appPath = tempStr;
	
	// 创建资源路径
	mapPath = appPath + _T("Maps\\");
	resPath = appPath + _T("Resources\\");
	CFileFind tempFind;
	if (tempFind.FindFile(mapPath, FILE_ATTRIBUTE_DIRECTORY) == 0)
	{
		CreateDirectory(mapPath, NULL);
	}
	if (tempFind.FindFile(resPath, FILE_ATTRIBUTE_DIRECTORY) == 0)
	{
		CreateDirectory(resPath, NULL);
	}

	/*
	// 全屏代码
	int cx, cy;
	cx = GetSystemMetrics(SM_CXSCREEN);
	cy = GetSystemMetrics(SM_CYSCREEN);
	CRect rcTemp;
	rcTemp.BottomRight() = CPoint(cx, cy);
	rcTemp.TopLeft() = CPoint(0, 0);
	MoveWindow(&rcTemp);
	*/

	// 实际大小 DIALOG_HEIGHT * DIALOG_WEIGHT
	const int DIALOG_HEIGHT = 700;
	const int DIALOG_WIDTH = 700;
	MoveWindow(0, 0, DIALOG_WIDTH, DIALOG_HEIGHT); // 初始大小
	CRect selfRect;
	this->GetClientRect(selfRect);
	MoveWindow(0, 0, DIALOG_WIDTH + DIALOG_WIDTH - selfRect.Width(), DIALOG_HEIGHT + DIALOG_HEIGHT - selfRect.Height()); // 修正大小
	CenterWindow(); // 居中
	
	// TESTSTART
	/*
	int cxf, cyf, cxb, cyb;
	CString str;
	cxf = GetSystemMetrics(SM_CXFIXEDFRAME);
	cyf = GetSystemMetrics(SM_CYFIXEDFRAME);
	cxb = GetSystemMetrics(SM_CXBORDER);
	cyb = GetSystemMetrics(SM_CYBORDER);
	str.Format(_T("cxf is %d, cyf is %d, cxb is %d, cyb is %d"), cxf, cyf, cxb, cyb);
	MessageBox(str, _T("xht"));
	CRect testRect;
	this->GetClientRect(testRect);
	str.Format(_T("top is %d, bottom is %d, left is %d, right is %d"), testRect.top, testRect.bottom, testRect.left, testRect.right);
	MessageBox(str, _T("xht"));
	*/
	// TESTEND

	// 载入子窗口
	myHomepage = new CHOMEPAGE;
	myHomepage->Create(IDD_HOMEPAGE, this);
	myHomepage->ShowWindow(SW_SHOW);

	myGame = new CGAME;
	myGame->Create(IDD_GAME, this);
	myGame->ShowWindow(SW_HIDE);

	mySelection = new CSELECTION;
	mySelection->Create(IDD_SELECTION, this);
	mySelection->ShowWindow(SW_HIDE);

	myHomepage->SetFocus();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CTXZDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTXZDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CTXZDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

LRESULT CTXZDlg::ToGame(WPARAM wParam, LPARAM lParam)
{
	if (!myGame->SendMessage(WM_STARTGAME, wParam))
	{
		MessageBox(_T("ERROR: 无法开始游戏"), _T("From xht"));
		return -1;
	}
	myHomepage->ShowWindow(SW_HIDE);
	mySelection->ShowWindow(SW_HIDE);
	myGame->ShowWindow(SW_SHOW);
	myGame->SetFocus();
	myGame->UpdateWindow();
	return 0;
}

LRESULT CTXZDlg::ToHomepage(WPARAM wParam, LPARAM lParam)
{
	myGame->ShowWindow(SW_HIDE);
	mySelection->ShowWindow(SW_HIDE);
	myHomepage->ShowWindow(SW_SHOW);
	myHomepage->SetFocus();
	myHomepage->UpdateWindow();
	return 0;
}

LRESULT CTXZDlg::ToSelection(WPARAM wParam, LPARAM lParam)
{
	myHomepage->ShowWindow(SW_HIDE);
	myGame->ShowWindow(SW_HIDE);
	mySelection->ShowWindow(SW_SHOW);
	mySelection->SetFocus();
	mySelection->UpdateWindow();
	return 0;
}

BOOL CTXZDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
#ifdef MYDEBUG
		switch (pMsg->wParam)
		{
		case VK_NUMPAD1:
			MessageBox(_T("!1"), _T("From xht"));
			break;
		case VK_UP:
			MessageBox(_T("!UP"), _T("From xht"));
			break;
		case VK_DOWN:
			MessageBox(_T("!DOWN"), _T("From xht"));
			break;
		case VK_LEFT:
			MessageBox(_T("!LEFT"), _T("From xht"));
			break;
		case VK_RIGHT:
			MessageBox(_T("!RIGHT"), _T("From xht"));
			break;
		case VK_ESCAPE:
			MessageBox(_T("!ESC"), _T("From xht"));
			break;
		/*default:
			return CDialogEx::PreTranslateMessage(pMsg);*/
		}
		//return TRUE;
#endif // MYDEBUG

		
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}

BOOL CTXZDlg::DestroyWindow()
{
	// TODO: 在此添加专用代码和/或调用基类
	myHomepage->DestroyWindow();
	delete myHomepage;
	myGame->DestroyWindow();
	delete myGame;
	mySelection->DestroyWindow();
	delete mySelection;
	return CDialogEx::DestroyWindow();
}
