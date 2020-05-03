#pragma once
#include "CRESOURCE.h"

// CBASE_Display �Ի���

class CBASE_Display : public CDialogEx
{
	DECLARE_DYNAMIC(CBASE_Display)

public:
	CBASE_Display(CRect area, CWnd* pParent = nullptr);   // ��׼���캯��
	virtual ~CBASE_Display();

	// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DISPLAY };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL DestroyWindow();
	/*�����ͷ��ڴ�ռ�*/
	virtual void Clear();
	/*����ʾ��������ػ�n*m�ķ���*/
	virtual BOOL Reset(int n, int m);
	/*���¸���(x,y)��ͼƬ��ʾ*/
	virtual void Update(int x, int y, UINT picTag, bool singleUpdate = TRUE);
protected:
	CRESOURCE* myRes;
	int m_size;
	CRect m_area;
	CStatic* m_pPictureMap[MAXMAPSIZE + 2][MAXMAPSIZE + 2];
	//CBitmap m_bitmap[PICNUM];
};