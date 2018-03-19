
#include "PsyjsmorFood.h"

PsyjsmorFood::PsyjsmorFood(PsyjsmorEngine* pEngine, PsyjsmorPlayer* pPlayer)
	: DisplayableObject(pEngine)
	, m_pMainEngine(pEngine)
	, m_pPlayer(pPlayer)
	, playerPosX(pPlayer->GetXCentre())
	, playerPosY(pPlayer->GetYCentre())
{
	// Food coords will be at centre
	m_iStartDrawPosX = m_iStartDrawPosY = -(iSize / 2);
	// Record food size
	m_iDrawHeight = m_iDrawWidth = iSize;
	// Food coords placed randomly
	m_iCurrentScreenX = m_iPreviousScreenX = (rand() % 17) * 40 + 60;
	m_iCurrentScreenY = m_iPreviousScreenY = (rand() % 11) * 40 + 100;
	// Make it visible
	SetVisible(true);
}

PsyjsmorFood::~PsyjsmorFood()
{
}

void PsyjsmorFood::Draw()
{
	if (m_pMainEngine->points < m_pMainEngine->winLimit)
	{
		m_pMainEngine->DrawForegroundOval(
			m_iCurrentScreenX - iSize,
			m_iCurrentScreenY - iSize,
			m_iCurrentScreenX + iSize - 1,
			m_iCurrentScreenY + iSize - 1,
			0x000000);

		m_pMainEngine->DrawForegroundOval(
			m_iCurrentScreenX - iSize + 2,
			m_iCurrentScreenY - iSize + 2,
			m_iCurrentScreenX + iSize - 3,
			m_iCurrentScreenY + iSize - 3,
			0xFF0000);

		StoreLastScreenPositionForUndraw();
	}
}

void PsyjsmorFood::DoUpdate(int iCurrentTime)
{
	if (m_pMainEngine->points < m_pMainEngine->winLimit)
	{
		m_iPreviousScreenX = m_iCurrentScreenX;
		m_iPreviousScreenY = m_iCurrentScreenY;

		playerPosX = m_pPlayer->GetXCentre();
		playerPosY = m_pPlayer->GetYCentre();

		if (playerPosX == m_iCurrentScreenX && playerPosY == m_iCurrentScreenY)
		{
			do
			{
				m_iCurrentScreenX = (rand() % 17) * 40 + 60;
				m_iCurrentScreenY = (rand() % 11) * 40 + 100;
			} while (m_iCurrentScreenX == m_iPreviousScreenX && m_iCurrentScreenY == m_iPreviousScreenY);
			m_pMainEngine->points++;
		}

		printf("Player: %d, %d - Food: %d, %d\n", playerPosX, playerPosY, m_iCurrentScreenX, m_iCurrentScreenY);

		RedrawObjects();
	}
}
