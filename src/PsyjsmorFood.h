#pragma once
#include "header.h"
#include "templates.h"
#include "PsyjsmorPlayer.h"
#include "PsyjsmorEngine.h"
#include "DisplayableObject.h"
class PsyjsmorFood :
	public DisplayableObject
{
public:
	PsyjsmorFood(PsyjsmorEngine*, PsyjsmorPlayer*);
	~PsyjsmorFood();
	void Draw();
	void DoUpdate(int);

private:
	PsyjsmorEngine* m_pMainEngine;
	PsyjsmorPlayer* m_pPlayer;

	int playerPosX;
	int playerPosY;
	int iSize = 10;
};
