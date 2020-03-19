#include "pch.h"
#include "CEDITOR_Map.h"

CEDITOR_Map::CEDITOR_Map(CEDITOR_Display* currentDisplay):
	myDisplay(currentDisplay)
{

}

CEDITOR_Map::~CEDITOR_Map()
{

}

void CEDITOR_Map::NewMap(int n, int m)
{
	myDisplay->Reset(n, m);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
		{
			m_map[i][j] = 0;
			myDisplay->Update(i, j, m_map[i][j]);
		}
}