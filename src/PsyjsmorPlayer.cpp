
#include "PsyjsmorPlayer.h"

PsyjsmorPlayer::PsyjsmorPlayer(PsyjsmorEngine* pEngine, int iMapX, int iMapY)
	: DisplayableObject(pEngine)
	, m_pMainEngine(pEngine)
	, m_iMapX(iMapX)
	, m_iMapY(iMapY)
	, m_iDir(0)
{
	// Player coordinate will be centre of the ball
	m_iStartDrawPosX = m_iStartDrawPosY = -15;
	// Record the players size
	m_iDrawHeight = m_iDrawWidth = 30;
	// Initially set previous and current equal
	m_iPreviousScreenX = m_iCurrentScreenX = iMapX * 40 + 60;
	m_iPreviousScreenY = m_iCurrentScreenY = iMapY * 40 + 100;
	// Make it visible
	SetVisible(true);
}

PsyjsmorPlayer::~PsyjsmorPlayer()
{
}

void PsyjsmorPlayer::Draw()
{
	int iSize = 15;

	m_pMainEngine->DrawForegroundOval(
		m_iCurrentScreenX - iSize,
		m_iCurrentScreenY - iSize,
		m_iCurrentScreenX + iSize - 1,
		m_iCurrentScreenY + iSize - 1,
		0x000000);

	m_pMainEngine->DrawForegroundOval(
		m_iCurrentScreenX - iSize + 3,
		m_iCurrentScreenY - iSize + 3,
		m_iCurrentScreenX + iSize - 4,
		m_iCurrentScreenY + iSize - 4,
		0x6CCA00);

	StoreLastScreenPositionForUndraw();
}

void PsyjsmorPlayer::DoUpdate(int iCurrentTime)
{
	if (m_pMainEngine->points < m_pMainEngine->winLimit)
	{
		m_iPreviousScreenX = m_iCurrentScreenX;
		m_iPreviousScreenY = m_iCurrentScreenY;

		if (!m_oMover.HasMovementFinished(iCurrentTime))
		{
			m_oMover.Calculate(iCurrentTime);
			m_iCurrentScreenX = m_oMover.GetX();
			m_iCurrentScreenY = m_oMover.GetY();
		}

		if (GetEngine()->IsKeyPressed(SDLK_UP) || GetEngine()->IsKeyPressed(SDLK_w))
			if (GetEngine()->IsKeyPressed(SDLK_LSHIFT))
				m_iCurrentScreenY = m_iPreviousScreenY - 80;
			else
				m_iCurrentScreenY = m_iPreviousScreenY - 40;
		if (GetEngine()->IsKeyPressed(SDLK_DOWN) || GetEngine()->IsKeyPressed(SDLK_s))
			if (GetEngine()->IsKeyPressed(SDLK_LSHIFT))
				m_iCurrentScreenY = m_iPreviousScreenY + 80;
			else
				m_iCurrentScreenY = m_iPreviousScreenY + 40;
		if (GetEngine()->IsKeyPressed(SDLK_LEFT) || GetEngine()->IsKeyPressed(SDLK_a))
			if (GetEngine()->IsKeyPressed(SDLK_LSHIFT))
				m_iCurrentScreenX = m_iPreviousScreenX - 80;
			else
				m_iCurrentScreenX = m_iPreviousScreenX - 40;
		if (GetEngine()->IsKeyPressed(SDLK_RIGHT) || GetEngine()->IsKeyPressed(SDLK_d))
			if (GetEngine()->IsKeyPressed(SDLK_LSHIFT))
				m_iCurrentScreenX = m_iPreviousScreenX + 80;
			else
				m_iCurrentScreenX = m_iPreviousScreenX + 40;

		if (m_iCurrentScreenX < m_iDrawWidth + m_iStartDrawPosX + 45)
			m_iCurrentScreenX = m_iDrawWidth + m_iStartDrawPosX + 45;
		if (m_iCurrentScreenX > GetEngine()->GetWindowWidth() - 60)
			m_iCurrentScreenX = GetEngine()->GetWindowWidth() - 60;
		//if (m_iCurrentScreenY < m_iDrawHeight + m_iStartDrawPosY + 85)
		//	m_iCurrentScreenY = m_iDrawHeight + m_iStartDrawPosY + 85;
		if (m_iCurrentScreenY < 20)
			m_iCurrentScreenY = 20;
		if (m_iCurrentScreenY > GetEngine()->GetWindowHeight() - 60)
			m_iCurrentScreenY = GetEngine()->GetWindowHeight() - 60;

		RedrawObjects();
	}

	if (m_pMainEngine->points >= m_pMainEngine->winLimit && GetEngine()->IsKeyPressed(SDLK_SPACE))
	{
		m_iPreviousScreenX = m_iCurrentScreenX;
		m_iPreviousScreenY = m_iCurrentScreenY;

		m_iCurrentScreenX = m_iMapX * 40 + 60;
		m_iCurrentScreenY = m_iMapY * 40 + 100;

		RedrawObjects();
	}
}
