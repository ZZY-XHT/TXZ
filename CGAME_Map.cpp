#include "pch.h"
#include "TXZ.h"
#include "CGAME_Map.h"
#include "afxdialogex.h"

CGAME_Map::CGAME_Map(CGAME_Display* currentDisplay):
	m_mapSizeX(0), m_mapSizeY(0),
	m_playerX(0), m_playerY(0),
	m_map(), m_isFinished(FALSE),
	m_Display(currentDisplay)
{
}

CGAME_Map::~CGAME_Map()
{
}

BOOL CGAME_Map::SetMap(CString path)
{
	// ����·�������ͼ
#ifdef MYDEBUG
	MessageBox(path, _T("From xht"));
#endif // MYDEBUG

	if (ReadMap(path))
	{
#ifdef MYDEBUG
		MessageBox(_T("��ȡ��ͼ�ɹ�"), _T("From xht"));
#endif // MYDEBUG

		// ��ʼ����
		m_Display->Reset(m_mapSizeX, m_mapSizeY);

		for (int i = 1; i <= m_mapSizeX; i++)
			for (int j = 1; j <= m_mapSizeY; j++)
			{
				m_Display->Update(i, j, m_map[i][j]);
			}

		m_Display->Update(m_playerX, m_playerY, PIC_PLAYER);

		//UpdateWindow();

		// ��ɻ���
		return TRUE;
	}
	else return FALSE;
}

// �Զ���Ķ�ȡ�Ǹ���������
const int MAXINPUTBUFFERSIZE = 100000;
char myInputBuffer[MAXINPUTBUFFERSIZE], * icp = myInputBuffer;
BOOL getNoneNegativeInteger(int& x, const int LOWERBOUND, const int UPPERBOUND)
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


BOOL CGAME_Map::ReadMap(CString path)
{
	MapAssert(PathFileExists(path), _T("ERROR����ͼ�ļ�������"));
	USES_CONVERSION; // Ϊ��ʹ��T2A/W2A��Unicode�µ�CStringתΪchar*��ռ��ջ�ռ䣬������ѭ�����ݹ���ʹ�ã�����ջ���
	char* pFileName = T2A(path); // ��ʱ����԰�T2A�ֶ�ʵ�����滻��

	FILE* pFile = NULL;
	if (pFileName != NULL)
	{
		fopen_s(&pFile, pFileName, "r");
		if (pFile != NULL)
		{
			int len = (int)fread(myInputBuffer, 1, MAXINPUTBUFFERSIZE, pFile);
			fclose(pFile);
			icp = myInputBuffer;
			MapAssert(len != MAXINPUTBUFFERSIZE, _T("ERROR����ͼ�ļ�����"));
			myInputBuffer[len] = '\0';
			// ��ʼ�����ͼ
			MapAssert(getNoneNegativeInteger(m_mapSizeX, 1, MAXMAPSIZE), _T("ERROR����ͼ�ߴ�Խ���ȱʧ"));
			MapAssert(getNoneNegativeInteger(m_mapSizeY, 1, MAXMAPSIZE), _T("ERROR����ͼ�ߴ�Խ���ȱʧ"));
			for (int i = 1; i <= m_mapSizeX; i++)
				for (int j = 1; j <= m_mapSizeY; j++)
					MapAssert(getNoneNegativeInteger(m_map[i][j], MP_FIRST, MP_LAST), _T("ERROR����ͼԪ��Խ���ȱʧ"));
			MapAssert(getNoneNegativeInteger(m_playerX, 1, MAXMAPSIZE), _T("ERROR�������ʼλ��Խ���ȱʧ"));
			MapAssert(getNoneNegativeInteger(m_playerY, 1, MAXMAPSIZE), _T("ERROR�������ʼλ��Խ���ȱʧ"));
			// ��ɶ����ͼ
			// ��ʼ�������ر߽�
			for (int i = 0; i <= m_mapSizeX + 1; i++)
				m_map[i][0] = m_map[i][m_mapSizeY + 1] = 4;
			for (int j = 1; j <= m_mapSizeY; j++)
				m_map[0][j] = m_map[m_mapSizeX + 1][j] = 4;
			// ��ɲ������ر߽�
			// ��ʼ����ͼ
			MapAssert(CanMoveOn(m_playerX, m_playerY), _T("ERROR�������ʼλ�������ӻ��ϰ���"));
			{
				int tempCount = 0;
				for (int i = 1; i <= m_mapSizeX; i++)
					for (int j = 1; j <= m_mapSizeY; j++)
						if (m_map[i][j] == MP_BOX) tempCount++;
						else if (m_map[i][j] == MP_GOAL) tempCount--;
				MapAssert(tempCount == 0, _T("ERROR��������Ŀ��������һ��"));
			}
			m_isFinished = FALSE;
			MapAssert(!IsFinished(), _T("ERROR����ͼ��ʼ״̬�����"));
			// ��ɼ���ͼ
			return TRUE;
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
			m_Display->Update(x, y, m_map[x][y]);
			m_Display->Update(xx, yy, PIC_PLAYER);
			//UpdateWindow();
			return TRUE;
			break;
		case MP_BOX:
		case MP_FINISH:
			if (CanMoveOn(xxx, yyy))
			{
				m_playerX = xx; m_playerY = yy;
				m_map[xx][yy] &= ~MP_BOX;
				m_map[xxx][yyy] |= MP_BOX;
				m_Display->Update(x, y, m_map[x][y]);
				m_Display->Update(xx, yy, PIC_PLAYER);
				m_Display->Update(xxx, yyy, m_map[xxx][yyy]);
				//UpdateWindow();
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
		//MessageBox(_T("ERROR�������ƶ�����Ƿ�"), _T("From xht"));
		return FALSE;
	}
	return FALSE;
}

BOOL CGAME_Map::IsFinished()
{
	for (int i = 1; i <= m_mapSizeX; i++)
		for (int j = 1; j <= m_mapSizeY; j++)
			if (m_map[i][j] == MP_BOX || m_map[i][j] == MP_GOAL)
			{
				return m_isFinished = FALSE;
			}
	return m_isFinished = TRUE;
}

BOOL CGAME_Map::CheckFinished()
{
	if (IsFinished())
	{
		MessageBox(0,_T("��ϲ���سɹ���"), _T("From xht"),0);
		return TRUE;
	}
	else return FALSE;
}