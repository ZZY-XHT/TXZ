#pragma once
#include "framework.h"
#include "CBASE_Map.h"
#include "CEDITOR_Display.h"
#include <stack>
class CEDITOR_Map :
	public CBASE_Map
{
public:
	CEDITOR_Map(CEDITOR_Display* currentDisplay);
	virtual ~CEDITOR_Map();
public:
	/*��ȡ��ͼ�����������ʼλ��*/
	virtual BOOL SetMap(CString path, BOOL checkValidity = true);

	/*����һ��n*m�Ŀհ׵�ͼ*/
	virtual void NewMap(int n, int m);

	/*�޸ĵ�r�е�c�У�������������޸�History*/
	virtual void ChangeMap(int r, int c, int delta);

	/*����ͼ��r�е�c�б����һ��״̬*/
	virtual void Change(int r, int c);

	/*��rc��Ӧ��λ�ñ����һ��״̬*/
	virtual void Change(int rc);

	/*������һ�β���*/
	virtual void Undo();

	/*��������*/
	virtual void Redo();

	/*�����Ƿ���Գ���*/
	virtual BOOL CanUndo();

	/*�����Ƿ��������*/
	virtual BOOL CanRedo();

	/*�ı������ʼλ��*/
	virtual void ChangePlayer(int rc);

	/*��ʾ����*/
	virtual void ShowPlayer();

	/*��������*/
	virtual void HidePlayer();

	/*���ص�ͼ�Ƿ��޸�*/
	virtual BOOL Modified();

	/*���redoHistory*/
	virtual void ClearRedoHistory();

	/*������*/
	virtual void doBackup();
private:
	std::stack<int> undoHistory, redoHistory;
	int m_bk_map[MAXMAPSIZE + 2][MAXMAPSIZE + 2];
	int m_bk_playerX, m_bk_playerY;
};

