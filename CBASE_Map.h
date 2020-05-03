#include "framework.h"
#include "CBASE_Display.h"
#define MapAssert(expr,msg)\
	if (!(expr))\
    {\
		if(m_popup) MessageBox(0,msg,_T("From xht"),0);\
		return FALSE;\
    }

#pragma once
class CBASE_Map
{
protected:
	CBASE_Map(CBASE_Display* currentDisplay);
	CBASE_Map(CBASE_Display* currentDisplay,bool doPopUp);
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
	/*根据当前的m_map更新m_display*/
	virtual void doRedraw();
public:
	/*从路径为path的文件中读取并绘制地图*/
	virtual BOOL SetMap(CString path);
protected:
	CBASE_Display* m_display;
	int m_mapSizeX, m_mapSizeY;
	int m_playerX, m_playerY;
	int m_map[MAXMAPSIZE + 2][MAXMAPSIZE + 2];
	bool m_isFinished;
	bool m_popup;
};

