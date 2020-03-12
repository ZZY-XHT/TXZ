#pragma once
class CRESOURCE
{
	//Todo: 记录m_dir，资源包选择界面
public:
	CRESOURCE();   // 标准构造函数
	virtual ~CRESOURCE();
public:
	static BOOL checkDir(CString dir);//弄成static到时候换资源界面可以用
	virtual HBITMAP getPic(int picTag);

private:
	const static CString m_idToFilename[10];
	static const int m_picCount = 6;
	CString m_dir = _T("./Resource/");
	HBITMAP m_bitmap[10];



};

