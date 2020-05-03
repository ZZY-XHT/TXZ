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
	/*���ַ���s�ж�ȡ��ͼ*/
	virtual BOOL GetMap(char* s);
	/*��·��Ϊpath���ļ��ж�ȡ��ͼ*/
	virtual BOOL ReadMap(CString path);
	/*�ж��˺������ܷ��ƶ�������(x,y)��*/
	virtual BOOL CanMoveOn(int x, int y);
	/*�����Ϸ�����Ƿ����*/
	virtual BOOL CheckFinished();
	/*���ݵ�ǰ��m_map����m_display*/
	virtual void doRedraw();
public:
	/*��·��Ϊpath���ļ��ж�ȡ�����Ƶ�ͼ*/
	virtual BOOL SetMap(CString path);
protected:
	CBASE_Display* m_display;
	int m_mapSizeX, m_mapSizeY;
	int m_playerX, m_playerY;
	int m_map[MAXMAPSIZE + 2][MAXMAPSIZE + 2];
	bool m_isFinished;
	bool m_popup;
};

