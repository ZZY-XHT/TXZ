#pragma once
class CRESOURCE
{
	// Todo: ��¼m_dir����Դ��ѡ�����
public:
	CRESOURCE();   // ��׼���캯��
	virtual ~CRESOURCE();
public:
	/*���dir�Ƿ���һ����Ч����ԴĿ¼*/
	static BOOL CheckDir(CString dir);

	/*��ȡ���ΪpicTag��ͼƬ*/
	virtual HBITMAP GetPic(int picTag);

private:
	/*picTag��Ӧ���ļ���*/
	static const CString m_idToFilename[10];
	static const int m_picCount = 7;
	CString m_dir = _T("./Resource/");
	HBITMAP m_bitmap[10];



};

