#pragma once
#include "framework.h"
#include "CBASE_Map.h"
#include "CEDITOR_Display.h"

class CEDITOR_Map:
	public CBASE_Map
{
public:
	CEDITOR_Map(CEDITOR_Display *currentDisplay);
	virtual ~CEDITOR_Map();
public:
	/*创建一个n*m的空白地图*/
	virtual void NewMap(int n, int m);

	//virtual void SaveMap();

private:
	CEDITOR_Display* myDisplay;
};

