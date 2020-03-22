#include "framework.h"

#define MapAssert(expr,msg)					\
	if (!(expr))						    \
    {										\
		MessageBox(0,msg,_T("From xht"),0); \
		return FALSE;						\
    }

#pragma once
class CBASE_Map
{
protected:
	CBASE_Map();
	virtual ~CBASE_Map();

protected:
	/*从字符串s中读取地图*/
	virtual BOOL GetMap(char* s);
	/*从路径为path的文件中读取地图*/
	virtual BOOL ReadMap(CString path);
	/*判断人和箱子能否移动到格子(x,y)上*/
	virtual BOOL CanMoveOn(int x, int y);
	/*检查游戏局面是否完成*/
	virtual BOOL CheckFinished();

protected:
	int m_mapSizeX, m_mapSizeY;
	int m_playerX, m_playerY;
	int m_map[MAXMAPSIZE + 2][MAXMAPSIZE + 2];
	bool m_isFinished;
};

