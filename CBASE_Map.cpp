#include "pch.h"
#include "CBASE_Map.h"

CBASE_Map::CBASE_Map(CBASE_Display* currentDisplay,bool doPopUp):
	m_popup(doPopUp),m_display(currentDisplay),
	m_mapSizeX(0), m_mapSizeY(0),
	m_playerX(0), m_playerY(0),
	m_map(), m_isFinished(FALSE)
{

}

CBASE_Map::~CBASE_Map()
{

}

// �Զ���Ķ�ȡ�Ǹ���������
BOOL getNoneNegativeInteger(char*& icp, int& x, const int LOWERBOUND, const int UPPERBOUND)
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

BOOL CBASE_Map::GetMap(char* s)
{
	// ��ʼ�����ͼ
	char* icp = s;
	MapAssert(getNoneNegativeInteger(icp, m_mapSizeX, 1, MAXMAPSIZE), _T("ERROR����ͼ�ߴ�Խ���ȱʧ"));
	MapAssert(getNoneNegativeInteger(icp, m_mapSizeY, 1, MAXMAPSIZE), _T("ERROR����ͼ�ߴ�Խ���ȱʧ"));
	for (int i = 1; i <= m_mapSizeX; i++)
		for (int j = 1; j <= m_mapSizeY; j++)
			MapAssert(getNoneNegativeInteger(icp, m_map[i][j], MP_FIRST, MP_LAST), _T("ERROR����ͼԪ��Խ���ȱʧ"));
	MapAssert(getNoneNegativeInteger(icp, m_playerX, 1, m_mapSizeX), _T("ERROR�������ʼλ��Խ���ȱʧ"));
	MapAssert(getNoneNegativeInteger(icp, m_playerY, 1, m_mapSizeY), _T("ERROR�������ʼλ��Խ���ȱʧ"));
	// ��ɶ����ͼ
	// ��ʼ�������ر߽�
	for (int i = 0; i <= m_mapSizeX + 1; i++)
		m_map[i][0] = m_map[i][m_mapSizeY + 1] = MP_WALL;
	for (int j = 1; j <= m_mapSizeY; j++)
		m_map[0][j] = m_map[m_mapSizeX + 1][j] = MP_WALL;
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
	MapAssert(!CheckFinished(), _T("ERROR����ͼ��ʼ״̬�����"));
	// ��ɼ���ͼ
	return TRUE;
}

BOOL CBASE_Map::ReadMap(CString path)
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
			const int MAXINPUTBUFFERSIZE = 100000;
			static char myInputBuffer[MAXINPUTBUFFERSIZE];
			int len = (int)fread(myInputBuffer, 1, MAXINPUTBUFFERSIZE, pFile);
			fclose(pFile);
			MapAssert(len != MAXINPUTBUFFERSIZE, _T("ERROR����ͼ�ļ�����"));
			myInputBuffer[len] = '\0';

			return GetMap(myInputBuffer);
		}
	}
	return FALSE;
}

BOOL CBASE_Map::SetMap(CString path)
{
	if (ReadMap(path))
	{
		doRedraw();
		return TRUE;
	}
	else return FALSE;
}

BOOL CBASE_Map::CanMoveOn(int x, int y)
{
	return ((1 <= x && x <= m_mapSizeX && 1 <= y && y <= m_mapSizeY) && !(m_map[x][y] & (MP_BOX | MP_WALL)));
}

BOOL CBASE_Map::CheckFinished()
{
	for (int i = 1; i <= m_mapSizeX; i++)
		for (int j = 1; j <= m_mapSizeY; j++)
			if (m_map[i][j] == MP_BOX || m_map[i][j] == MP_GOAL)
			{
				return m_isFinished = FALSE;
			}
	return m_isFinished = TRUE;
}

void CBASE_Map::doRedraw()
{
	m_display->Reset(m_mapSizeX, m_mapSizeY);
	for (int i = 1; i <= m_mapSizeX; i++)
		for (int j = 1; j <= m_mapSizeY; j++)
		{
			m_display->Update(i, j, m_map[i][j], FALSE);
		}
	m_display->Update(m_playerX, m_playerY, PIC_PLAYER);
	m_display->UpdateWindow();
}