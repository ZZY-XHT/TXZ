#pragma once

#define SZ_EXTRALARGE 90
#define SZ_LARGE 60
#define SZ_NORMAL 45
#define SZ_SMALL 30
#define SZ_EXTRASMALL 18

#define NUM_EXTRALARGE 6
#define NUM_LARGE 9
#define NUM_NORMAL 12
#define NUM_SMALL 18
#define NUM_EXTRASMALL 30

#define DIR_UP 0
#define DIR_DOWN 1
#define DIR_LEFT 2
#define DIR_RIGHT 3
#define DIR_FIRST 0
#define DIR_LAST 3

const int MAXMAPSIZE = 30;

const int dx[4] = { -1, 1, 0, 0 };
const int dy[4] = { 0, 0, -1, 1 };


// CGAME 对话框

class CGAME : public CDialogEx
{
	DECLARE_DYNAMIC(CGAME)

public:
	CGAME(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CGAME();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAME };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL DestroyWindow();
	afx_msg void OnBnClickedReturn();
	afx_msg LRESULT StartGame(WPARAM wParam, LPARAM lParam);
protected:
	virtual BOOL SetMap(CString path);
	virtual BOOL Clear();
	virtual BOOL ReadMap(CString path);
	virtual BOOL PaintMap(int x, int y, UINT picTag);
	virtual BOOL MovePlayer(UINT dir);
	virtual BOOL CanMoveOn(int x, int y);
	virtual BOOL CheckFinished();
	virtual BOOL IsFinished();
private:
	int m_map[MAXMAPSIZE + 2][MAXMAPSIZE + 2];
	int m_mapSizeX, m_mapSizeY;
	int m_playerX, m_playerY;
	CStatic* m_pPictureMap[MAXMAPSIZE + 2][MAXMAPSIZE + 2];
	CBitmap m_bitmap[PICNUM];
	int m_size, m_offsetX, m_offsetY;
	bool m_isFinished;
	CFont m_font;
};
