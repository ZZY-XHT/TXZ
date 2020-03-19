#include "framework.h"
#include "CEDITOR_Display.h"
#pragma once
class CEDITOR_Map
{
public:
	CEDITOR_Map(CEDITOR_Display *currentDisplay);
	virtual ~CEDITOR_Map();
public:
	virtual void NewMap(int n,int m);
	//virtual void SaveMap();

private:
	int m_map[MAXMAPSIZE + 2][MAXMAPSIZE + 2];
	int m_mapSizeX, m_mapSizeY;
	CEDITOR_Display* myDisplay;
};

