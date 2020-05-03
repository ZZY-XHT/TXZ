// CBASE_Display.cpp: ʵ���ļ�
//

#include "pch.h"
#include "TXZ.h"
#include "CBASE_Display.h"
#include "afxdialogex.h"


// CBASE_Display �Ի���

IMPLEMENT_DYNAMIC(CBASE_Display, CDialogEx)

CBASE_Display::CBASE_Display(CRect area, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DISPLAY, pParent),
	m_size(1), m_area(area)
{
	Clear();
	myRes = new CRESOURCE();
}

CBASE_Display::~CBASE_Display()
{
}

void CBASE_Display::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CBASE_Display, CDialogEx)
END_MESSAGE_MAP()


// CBASE_Display ��Ϣ�������

BOOL CBASE_Display::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}

BOOL CBASE_Display::DestroyWindow()
{
	// TODO: �ڴ����ר�ô����/����û���
	Clear();
	if (myRes != NULL) delete myRes;
	return CDialogEx::DestroyWindow();
}

void CBASE_Display::Clear()
{
	// �ͷſؼ�����
	for (int i = 0; i < MAXMAPSIZE + 2; i++)
		for (int j = 0; j < MAXMAPSIZE + 2; j++)
			if (m_pPictureMap[i][j] != NULL)
			{
				delete m_pPictureMap[i][j];
				m_pPictureMap[i][j] = NULL;
			}
}

BOOL CBASE_Display::Reset(int n, int m)
{
	ShowWindow(SW_HIDE);
	Clear();
	m_size = min(m_area.Height() / n, m_area.Width() / m);
	MoveWindow(m_area.left + (m_area.Width() - m * m_size) / 2, m_area.top + (m_area.Height() - n * m_size) / 2, m * m_size, n * m_size);


	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
		{
			CStatic*& p = m_pPictureMap[i][j];
			if (p != NULL)
			{
				MessageBox(_T("SERIOUS ERROR: Gameָ���ʼ�ǿ�"), _T("From xht"));
				GetParent()->GetParent()->PostMessage(WM_CLOSE);
				return FALSE;
			}
			p = new CStatic();
			p->Create(NULL, SS_BITMAP, CRect((j - 1) * m_size, (i - 1) * m_size, m_size, m_size), this, IDC_D_BMP + i * (MAXMAPSIZE + 2) + j);
		}
	ShowWindow(SW_SHOW);
	return TRUE;
}

void CBASE_Display::Update(int x, int y, UINT picTag, bool singleUpdate)
{
	m_pPictureMap[x][y]->ShowWindow(SW_HIDE);
	m_pPictureMap[x][y]->SetBitmap(myRes->GetPic(picTag));
	m_pPictureMap[x][y]->MoveWindow((y - 1) * m_size, (x - 1) * m_size, m_size, m_size);
	m_pPictureMap[x][y]->ShowWindow(SW_SHOW);

	if (singleUpdate)
	{
		UpdateWindow();
	}
}