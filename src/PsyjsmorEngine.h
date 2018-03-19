#pragma once
#include "header.h"
#include "templates.h"
#include "BaseEngine.h"
#include "TileManager.h"
#include "PsyjsmorTileManager.h"
class PsyjsmorEngine :
	public BaseEngine
{
public:
	PsyjsmorEngine();
	~PsyjsmorEngine();
	void SetupBackgroundBuffer();
	int InitialiseObjects();
	void GameAction();
	void UnDrawStrings();
	void DrawStringsUnderneath();
	void DrawStringsOnTop();
	PsyjsmorTileManager& GetTileManager() { return m_oTiles; }

	int points = 0;
	int winLimit = 10;
private:
	PsyjsmorTileManager m_oTiles;
};
