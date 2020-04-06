#include "pch.h"
#include "CEDITOR_Map.h"

CEDITOR_Map::CEDITOR_Map(CEDITOR_Display* currentDisplay): 
	CBASE_Map(),
	myDisplay(currentDisplay)
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

void CEDITOR_Map::ChangeMap(int r, int c) {
	m_map[r][c] = (m_map[r][c] + 1) % 5;
	myDisplay->Update(r, c, m_map[r][c]);
	undoHistory.push(1000 * r + c);
}

void CEDITOR_Map::UndoChangeMap(int r, int c) {
	m_map[r][c] = (m_map[r][c] + 4) % 5;
	myDisplay->Update(r, c, m_map[r][c]);
}

void CEDITOR_Map::Undo() {
	int tmp = undoHistory.top();
	undoHistory.pop();
	redoHistory.push(tmp);
	UndoChangeMap(tmp / 1000, tmp % 1000);
}

void CEDITOR_Map::Redo() {
	int tmp = redoHistory.top();
	redoHistory.pop();
	ChangeMap(tmp / 1000, tmp % 1000);
}
