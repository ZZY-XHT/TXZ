#include "CBASE_Map.h"
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

class CGAME_Map:
	public CBASE_Map
{

public:
	CGAME_Map(CGAME_Display* currentDisplay);   // ��׼���캯��
	virtual ~CGAME_Map();

public:
	/*��·��Ϊpath���ļ��ж�ȡ�����Ƶ�ͼ*/
	virtual BOOL SetMap(CString path);
	/*���¿�ʼ������Ϸ*/
	virtual BOOL Restart();
	/*������dir�����ƶ����*/
	virtual BOOL MovePlayer(UINT dir);
	/*��ȡ������Ϸ�Ƿ���ɵ���Ϣ*/
	virtual BOOL IsFinished();

private:
	CGAME_Display* m_display;
	int m_bk_map[MAXMAPSIZE + 2][MAXMAPSIZE + 2];
	int m_bk_playerX, m_bk_playerY;
};