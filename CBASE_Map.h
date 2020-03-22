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
	/*���ַ���s�ж�ȡ��ͼ*/
	virtual BOOL GetMap(char* s);
	/*��·��Ϊpath���ļ��ж�ȡ��ͼ*/
	virtual BOOL ReadMap(CString path);
	/*�ж��˺������ܷ��ƶ�������(x,y)��*/
	virtual BOOL CanMoveOn(int x, int y);
	/*�����Ϸ�����Ƿ����*/
	virtual BOOL CheckFinished();

protected:
	int m_mapSizeX, m_mapSizeY;
	int m_playerX, m_playerY;
	int m_map[MAXMAPSIZE + 2][MAXMAPSIZE + 2];
	bool m_isFinished;
};

