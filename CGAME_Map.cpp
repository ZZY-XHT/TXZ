#include "pch.h"
#include "TXZ.h"
#include "CGAME_Map.h"
#include "afxdialogex.h"

CGAME_Map::CGAME_Map(CGAME_Display* currentDisplay):
	m_mapSizeX(0), m_mapSizeY(0),
	m_playerX(0), m_playerY(0),
	m_map(), m_isFinished(FALSE),
	m_display(currentDisplay),
	m_bk_map(),
	m_bk_playerX(0), m_bk_playerY(0)
{
}

CGAME_Map::~CGAME_Map()
{
}

BOOL CGAME_Map::SetMap(CString path)
{
	// 根据路径载入地图
#ifdef MYDEBUG
	MessageBox(path, _T("From xht"));
#endif // MYDEBUG

	if (ReadMap(path))
	{
#ifdef MYDEBUG
		MessageBox(_T("读取地图成功"), _T("From xht"));
#endif // MYDEBUG

		// 开始绘制
		m_display->Reset(m_mapSizeX, m_mapSizeY);

		for (int i = 1; i <= m_mapSizeX; i++)
			for (int j = 1; j <= m_mapSizeY; j++)
			{
				m_display->Update(i, j, m_map[i][j]);
			}

		m_display->Update(m_playerX, m_playerY, PIC_PLAYER);

		// UpdateWindow();

		// 完成绘制
		return TRUE;
	}
	else return FALSE;
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

// 自定义的读取非负整数函数
BOOL getNoneNegativeInteger(char* &icp, int& x, const int LOWERBOUND, const int UPPERBOUND)
{
	long long tempValue = 0LL;
	while (!isdigit(static_cast<unsigned char>(*icp)))
	{
		if (*icp == '\n' || *icp == '\r' || *icp == ' ') icp++;
		else return FALSE;
	}
	while (isdigit(static_cast<unsigned char>(*icp)))
	{
		tempValue = tempValue * 10 + *icp - '0';
		if (tempValue <= UPPERBOUND) icp++;
		else return FALSE;
	}
	if (LOWERBOUND <= tempValue && tempValue <= UPPERBOUND)
	{
		x = (int)tempValue;
		return TRUE;
	}
	else return FALSE;
}

BOOL CGAME_Map::GetMap(char *s)
{
	// 开始读入地图
	char* icp = s;
	MapAssert(getNoneNegativeInteger(icp, m_mapSizeX, 1, MAXMAPSIZE), _T("ERROR：地图尺寸越界或缺失"));
	MapAssert(getNoneNegativeInteger(icp, m_mapSizeY, 1, MAXMAPSIZE), _T("ERROR：地图尺寸越界或缺失"));
	for (int i = 1; i <= m_mapSizeX; i++)
		for (int j = 1; j <= m_mapSizeY; j++)
			MapAssert(getNoneNegativeInteger(icp, m_map[i][j], MP_FIRST, MP_LAST), _T("ERROR：地图元素越界或缺失"));
	MapAssert(getNoneNegativeInteger(icp, m_playerX, 1, m_mapSizeX), _T("ERROR：人物初始位置越界或缺失"));
	MapAssert(getNoneNegativeInteger(icp, m_playerY, 1, m_mapSizeY), _T("ERROR：人物初始位置越界或缺失"));
	// 完成读入地图
	// 开始补充隐藏边界
	for (int i = 0; i <= m_mapSizeX + 1; i++)
		m_map[i][0] = m_map[i][m_mapSizeY + 1] = MP_WALL;
	for (int j = 1; j <= m_mapSizeY; j++)
		m_map[0][j] = m_map[m_mapSizeX + 1][j] = MP_WALL;
	// 完成补充隐藏边界
	// 开始检查地图
	MapAssert(CanMoveOn(m_playerX, m_playerY), _T("ERROR：人物初始位置在箱子或障碍上"));
	{
		int tempCount = 0;
		for (int i = 1; i <= m_mapSizeX; i++)
			for (int j = 1; j <= m_mapSizeY; j++)
				if (m_map[i][j] == MP_BOX) tempCount++;
				else if (m_map[i][j] == MP_GOAL) tempCount--;
		MapAssert(tempCount == 0, _T("ERROR：箱子与目标数量不一致"));
	}
	m_isFinished = FALSE;
	MapAssert(!CheckFinished(), _T("ERROR：地图初始状态已完成"));
	// 完成检查地图
	// 开始备份地图
	for (int i = 1; i <= m_mapSizeX; i++)
		for (int j = 1; j <= m_mapSizeY; j++)
			m_bk_map[i][j] = m_map[i][j];
	m_bk_playerX = m_playerX;
	m_bk_playerY = m_playerY;
	// 完成备份地图
	return TRUE;
}

BOOL CGAME_Map::ReadMap(CString path)
{
	MapAssert(PathFileExists(path), _T("ERROR：地图文件不存在"));
	USES_CONVERSION; // 为了使用T2A/W2A将Unicode下的CString转为char*，占用栈空间，不宜在循环、递归中使用，以免栈溢出
	char* pFileName = T2A(path); // 有时间可以把T2A手动实现来替换掉

	FILE* pFile = NULL;
	if (pFileName != NULL)
	{
		fopen_s(&pFile, pFileName, "r");
		if (pFile != NULL)
		{
			const int MAXINPUTBUFFERSIZE = 100000;
			static char myInputBuffer[MAXINPUTBUFFERSIZE];
			int len = (int)fread(myInputBuffer, 1, MAXINPUTBUFFERSIZE, pFile);
			fclose(pFile);
			MapAssert(len != MAXINPUTBUFFERSIZE, _T("ERROR：地图文件过大"));
			myInputBuffer[len] = '\0';
			
			return GetMap(myInputBuffer);
		}
	}
	return FALSE;
}

BOOL CGAME_Map::CanMoveOn(int x, int y)
{
	return ((1 <= x && x <= m_mapSizeX && 1 <= y && y <= m_mapSizeY) && !(m_map[x][y] & (MP_BOX | MP_WALL)));
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

BOOL CGAME_Map::CheckFinished()
{
	for (int i = 1; i <= m_mapSizeX; i++)
		for (int j = 1; j <= m_mapSizeY; j++)
			if (m_map[i][j] == MP_BOX || m_map[i][j] == MP_GOAL)
			{
				return m_isFinished = FALSE;
			}
	return m_isFinished = TRUE;
}

BOOL CGAME_Map::IsFinished()
{
	return m_isFinished;
}