#pragma once
class CRESOURCE
{
	//Todo: ��¼m_dir����Դ��ѡ�����
public:
	CRESOURCE();   // ��׼���캯��
	virtual ~CRESOURCE();
public:
	static BOOL checkDir(CString dir);//Ū��static��ʱ����Դ���������
	virtual HBITMAP getPic(int picTag);

private:
	const static CString m_idToFilename[10];
	static const int m_picCount = 6;
	CString m_dir = _T("./Resource/");
	HBITMAP m_bitmap[10];



};

