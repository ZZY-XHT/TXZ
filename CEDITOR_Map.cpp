#include "pch.h"
#include "CEDITOR_Map.h"

CEDITOR_Map::CEDITOR_Map(CEDITOR_Display* currentDisplay):
	myDisplay(currentDisplay),
	m_mapSizeX(0), m_mapSizeY(0),
	m_map()
{

}

CEDITOR_Map::~CEDITOR_Map()
{

}

void CEDITOR_Map::NewMap(int n, int m)
{
	myDisplay->Reset(n, m);
	MessageBox(0, _T("..."), _T("From xht"), 0);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
		{
			m_map[i][j] = PIC_NULL;
			myDisplay->Update(i, j, m_map[i][j]);
		}
}