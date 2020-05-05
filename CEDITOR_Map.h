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
	/*读取地图，并且人物初始位置*/
	virtual BOOL SetMap(CString path, BOOL checkValidity = true);

	/*创建一个n*m的空白地图*/
	virtual void NewMap(int n, int m);

	/*修改第r行第c列，这个函数不会修改History*/
	virtual void ChangeMap(int r, int c, int delta);

	/*将地图第r行第c列变成下一个状态*/
	virtual void Change(int r, int c);

	/*将rc对应的位置变成下一个状态*/
	virtual void Change(int rc);

	/*撤销上一次操作*/
	virtual void Undo();

	/*重做操作*/
	virtual void Redo();

	/*返回是否可以撤销*/
	virtual BOOL CanUndo();

	/*返回是否可以重做*/
	virtual BOOL CanRedo();

	/*改变人物初始位置*/
	virtual void ChangePlayer(int rc);

	/*显示人物*/
	virtual void ShowPlayer();

	/*隐藏人物*/
	virtual void HidePlayer();

	/*返回地图是否被修改*/
	virtual BOOL Modified();

	/*清空redoHistory*/
	virtual void ClearRedoHistory();

	/*做备份*/
	virtual void doBackup();
private:
	std::stack<int> undoHistory, redoHistory;
	int m_bk_map[MAXMAPSIZE + 2][MAXMAPSIZE + 2];
	int m_bk_playerX, m_bk_playerY;
};

