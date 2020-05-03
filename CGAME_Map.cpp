#include "pch.h"
#include "TXZ.h"
#include "CGAME_Map.h"
#include "afxdialogex.h"

CGAME_Map::CGAME_Map(CGAME_Display* currentDisplay):
	CBASE_Map(currentDisplay),
	m_bk_map(),
	m_bk_playerX(0), m_bk_playerY(0)
{
}

CGAME_Map::~CGAME_Map()
{
}

BOOL CGAME_Map::SetMap(CString path)
{
	if (CBASE_Map::SetMap(path))
	{
		doBackup();
		return TRUE;
	}
	else return FALSE;
}

void CGAME_Map::doBackup()
{
	for (int i = 1; i <= m_mapSizeX; i++)
		for (int j = 1; j <= m_mapSizeY; j++)
			m_bk_map[i][j] = m_map[i][j];
	m_bk_playerX = m_playerX;
	m_bk_playerY = m_playerY;
}

BOOL CGAME_Map::Restart()
{
	// 读取备份
	for (int i = 1; i <= m_mapSizeX; i++)
		for (int j = 1; j <= m_mapSizeY; j++)
			m_map[i][j] = m_bk_map[i][j];
	m_playerX = m_bk_playerX;
	m_playerY = m_bk_playerY;
	m_isFinished = FALSE;

	// 重绘
	for (int i = 1; i <= m_mapSizeX; i++)
		for (int j = 1; j <= m_mapSizeY; j++)
		{
			m_display->Update(i, j, m_map[i][j]);
		}
	m_display->Update(m_playerX, m_playerY, PIC_PLAYER);
	return TRUE;
}


BOOL CGAME_Map::MovePlayer(UINT dir)
{
	if (m_isFinished)
	{
		return FALSE;
	}
	if (DIR_FIRST <= dir && dir <= DIR_LAST)
	{
		int x = m_playerX, y = m_playerY;
		int xx = x + dx[dir], yy = y + dy[dir];
		int xxx = xx + dx[dir], yyy = yy + dy[dir];
		switch (m_map[xx][yy])
		{
		case MP_NULL:
		case MP_GOAL:
			m_playerX = xx; m_playerY = yy;
			m_display->Update(x, y, m_map[x][y]);
			m_display->Update(xx, yy, PIC_PLAYER);
			// UpdateWindow();
			return TRUE;
			break;
		case MP_BOX:
		case MP_FINISH:
			if (CanMoveOn(xxx, yyy))
			{
				m_playerX = xx; m_playerY = yy;
				m_map[xx][yy] &= ~MP_BOX;
				m_map[xxx][yyy] |= MP_BOX;
				m_display->Update(x, y, m_map[x][y]);
				m_display->Update(xx, yy, PIC_PLAYER);
				m_display->Update(xxx, yyy, m_map[xxx][yyy]);
				// UpdateWindow();
				CheckFinished();
				return TRUE;
			}
			else
			{
				return FALSE;
			}
			break;
		case MP_WALL:
		default:
			break;
		}
		return FALSE;
	}
	else
	{
		// MessageBox(_T("ERROR：人物移动方向非法"), _T("From xht"));
		return FALSE;
	}
	return FALSE;
}

BOOL CGAME_Map::IsFinished()
{
	return m_isFinished;
}