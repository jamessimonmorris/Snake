#pragma once
#include "header.h"
#include "templates.h"
#include "PsyjsmorEngine.h"
#include "MovementPosition.h"
#include "DisplayableObject.h"
class PsyjsmorPlayer :
	public DisplayableObject
{
public:
	PsyjsmorPlayer(PsyjsmorEngine*, int, int);
	~PsyjsmorPlayer();
	void Draw();
	void DoUpdate(int);

private:
	PsyjsmorEngine* m_pMainEngine;
	MovementPosition m_oMover;

	int m_iMapX;
	int m_iMapY;
	int m_iDir;
};
