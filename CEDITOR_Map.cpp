#include "pch.h"
#include "CEDITOR_Map.h"

CEDITOR_Map::CEDITOR_Map(CEDITOR_Display* currentDisplay) :
	CBASE_Map(currentDisplay),
	m_bk_map(),
	m_bk_playerX(-1), m_bk_playerY(-1)
{

}

CEDITOR_Map::~CEDITOR_Map()
{

}

BOOL CEDITOR_Map::SetMap(CString path, BOOL checkValidity)
{
	if (CBASE_Map::SetMap(path, checkValidity))
	{
		doBackup();
		return TRUE;
	}
	else return FALSE;
}

void CEDITOR_Map::NewMap(int n, int m)
{
#ifdef MYDEBUG
	MessageBox(0, _T("..."), _T("From xht"), 0);
#endif // MYDEBUG
	m_mapSizeX = n; m_mapSizeY = m;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			m_map[i][j] = PIC_NULL;
	m_playerX = 1; m_playerY = 1;
	doBackup();
	m_bk_playerX = -1; m_bk_playerY = -1;
	doRedraw();
}

void CEDITOR_Map::ChangeMap(int r, int c, int delta)
{
	m_map[r][c] = (m_map[r][c] + delta + 5) % 5;
	m_display->Update(r, c, m_map[r][c]);
}

void CEDITOR_Map::Change(int r, int c)
{
	ChangeMap(r, c, 1);
	undoHistory.push(1024 * r + c);
}

void CEDITOR_Map::Change(int rc)
{
	ChangeMap(rc / 1024, rc % 1024, 1);
	undoHistory.push(rc);
}

void CEDITOR_Map::Undo()
{
	if (!undoHistory.empty())
	{
		int rc = undoHistory.top();
		undoHistory.pop();
		redoHistory.push(rc);
		ChangeMap(rc / 1024, rc % 1024, -1);
	}
	else
	{
		MessageBox(NULL, _T("û�в�����"), _T("�޷�Undo"), 0);
	}
}

void CEDITOR_Map::Redo()
{
	if (!redoHistory.empty())
	{
		int rc = redoHistory.top();
		redoHistory.pop();
		Change(rc);
	}
	else
	{
		MessageBox(NULL, _T("û�в�����"), _T("�޷�Redo"), 0);
	}
}

BOOL CEDITOR_Map::CanUndo()
{
	return !undoHistory.empty();
}

BOOL CEDITOR_Map::CanRedo()
{
	return !redoHistory.empty();
}

void CEDITOR_Map::ChangePlayer(int rc)
{
	int r = rc / 1024, c = rc % 1024;
	HidePlayer();
	m_playerX = r; m_playerY = c;
	ShowPlayer();
}

void CEDITOR_Map::ShowPlayer()
{
	m_display->Update(m_playerX, m_playerY, PIC_PLAYER);
}

void CEDITOR_Map::HidePlayer()
{
	m_display->Update(m_playerX, m_playerY, m_map[m_playerX][m_playerY]);
}

BOOL CEDITOR_Map::Modified()
{
	//�½��ĵ�ͼbk_playerX,Y����-1�����Ա����Ǳ��޸ĵ�
	for (int i = 1; i <= m_mapSizeX; i++)
		for (int j = 1; j <= m_mapSizeY; j++)
			if (m_map[i][j] != m_bk_map[i][j]) return TRUE;
	return (m_playerX != m_bk_playerX) || (m_playerY != m_bk_playerY);
}

void CEDITOR_Map::ClearRedoHistory()
{
	while (!redoHistory.empty()) redoHistory.pop();
}

void CEDITOR_Map::doBackup()
{
	for (int i = 1; i <= m_mapSizeX; i++)
		for (int j = 1; j <= m_mapSizeY; j++)
			m_bk_map[i][j] = m_map[i][j];
	m_bk_playerX = m_playerX;
	m_bk_playerY = m_playerY;
}
