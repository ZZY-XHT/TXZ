#pragma once
class CRESOURCE
{
	// Todo: 记录m_dir，资源包选择界面
public:
	CRESOURCE();   // 标准构造函数
	virtual ~CRESOURCE();
public:
	/*检查dir是否是一个有效的资源目录*/
	static BOOL CheckDir(CString dir);

	/*获取标号为picTag的图片*/
	virtual HBITMAP GetPic(int picTag);

private:
	/*picTag对应的文件名*/
	static const CString m_idToFilename[10];
	static const int m_picCount = 7;
	CString m_dir = _T("./Resource/");
	HBITMAP m_bitmap[10];



};

