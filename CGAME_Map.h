#include "CGAME_Display.h"
#pragma once


#define DIR_UP 0
#define DIR_DOWN 1
#define DIR_LEFT 2
#define DIR_RIGHT 3
#define DIR_FIRST 0
#define DIR_LAST 3

const int dx[4] = { -1, 1, 0, 0 };
const int dy[4] = { 0, 0, -1, 1 };

#define MapAssert(expr,msg)					\
	if (!(expr))						    \
    {										\
		MessageBox(0,msg,_T("From xht"),0); \
		return FALSE;						\
    }

class CGAME_Map
{

public:
	CGAME_Map(CGAME_Display* currentDisplay);   // 标准构造函数
	virtual ~CGAME_Map();

protected:
	virtual BOOL GetMap(char *s);
	virtual BOOL ReadMap(CString path);
	virtual BOOL CanMoveOn(int x, int y);
	virtual BOOL CheckFinished();
	virtual BOOL IsFinished();

public:
	virtual BOOL SetMap(CString path);
	virtual BOOL Restart();
	virtual BOOL MovePlayer(UINT dir);

private:
	int m_map[MAXMAPSIZE + 2][MAXMAPSIZE + 2];
	int m_mapSizeX, m_mapSizeY;
	int m_playerX, m_playerY;
	bool m_isFinished;
	CGAME_Display* m_Display;

	int m_bk_map[MAXMAPSIZE + 2][MAXMAPSIZE + 2];
	int m_bk_playerX, m_bk_playerY;
};