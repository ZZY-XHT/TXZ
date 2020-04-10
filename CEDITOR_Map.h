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

	/**/
	virtual void Redo();
	//virtual void SaveMap();

private:
	CEDITOR_Display* myDisplay;
	std::stack<int> undoHistory, redoHistory;

};

