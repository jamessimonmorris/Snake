
#include "PsyjsmorEngine.h"
#include "PsyjsmorPlayer.h"
#include "PsyjsmorFood.h"

PsyjsmorEngine::PsyjsmorEngine()
{
}

PsyjsmorEngine::~PsyjsmorEngine()
{
}

void PsyjsmorEngine::SetupBackgroundBuffer()
{
	FillBackground(0x71aa7e);
	DrawBackgroundRectangle(0, 0, GetWindowWidth()-1, 39, 0x44714e);

	// TileManager Grid to determine border
	const char* tiles[] = {
		"xxxxxxxxxxxxxxxxxxxx",
		"xbbbbbbbbbbbbbbbbbbx",
		"xbbbbbbbbbbbbbbbbbbx",
		"xbbbbbbbbbbbbbbbbbbx",
		"xbbbbbbbbbbbbbbbbbbx",
		"xbbbbbbbbbbbbbbbbbbx",
		"xbbbbbbbbbbbbbbbbbbx",
		"xbbbbbbbbbbbbbbbbbbx",
		"xbbbbbbbbbbbbbbbbbbx",
		"xbbbbbbbbbbbbbbbbbbx",
		"xbbbbbbbbbbbbbbbbbbx",
		"xbbbbbbbbbbbbbbbbbbx",
		"xbbbbbbbbbbbbbbbbbbx",
		"xxxxxxxxxxxxxxxxxxxx" };

	// Specify how many tiles wide and high the grid is
	m_oTiles.SetSize(20, 14);
	// Assign each tile a value
	for (int x = 0; x < 20; x++)
		for (int y = 0; y < 14; y++)
			m_oTiles.SetValue(x, y, tiles[y][x] - 'x');
	// Print each tile's value
	for (int y = 0; y < 14; y++)
	{
		for (int x = 0; x < 20; x++)
			printf("%d ", m_oTiles.GetValue(x, y));
		printf("\n");
	}
	// Specify the screen x,y of top left corner
	m_oTiles.SetBaseTilesPositionOnScreen(0, 40);
	// Draw all tiles from x1,y1 to x2,y2
	m_oTiles.DrawAllTiles(this, this->GetBackground(), 0, 0, 19, 13);
}

int PsyjsmorEngine::InitialiseObjects()
{
	// Record the fact that we are about to change the array - so it doesn't get 
	// used elsewhere without reloading it
	DrawableObjectsChanged();

	// Destroy any existing objects
	DestroyOldObjects();

	// Creates an array to store the objects
	// Needs to have room for the NULL at the end
	CreateObjectArray(3);

	// You MUST set the array entry after the last one that you create to NULL, so 
	// that the system knows when to stop.
	// i.e. The LAST entry has to be NULL. The fact that it is NULL is used in 
	// order to work out where the end of the array is.
	PsyjsmorPlayer* player = new PsyjsmorPlayer(this, 9, 5); // x <= 17, y <= 11

	StoreObjectInArray(0, new PsyjsmorFood(this, player));
	StoreObjectInArray(1, player);
	StoreObjectInArray(2, NULL);

	return 0;
}

void PsyjsmorEngine::GameAction()
{
	// If too early to act then do nothing
	if (!IsTimeToAct())
		return;
	// Don't act for another 400 ticks
	SetTimeToAct(200);

	UpdateAllObjects(GetTime());

	if (points >= winLimit && IsKeyPressed(SDLK_SPACE))
	{
		points = 0;
	}
}

void PsyjsmorEngine::UnDrawStrings()
{
	CopyBackgroundPixels(0, 0, GetWindowWidth(), 350);
}

void PsyjsmorEngine::DrawStringsUnderneath()
{
	char buf[64];
	sprintf(buf, "%d", points);
	DrawBackgroundString(50, 10, "Points:", 0xFFFFFF, NULL);
	DrawForegroundString(150, 10, buf, 0xFFFFFF, NULL);
}

void PsyjsmorEngine::DrawStringsOnTop()
{
	if (points >= winLimit)
	{
		DrawForegroundString(150, 295, "Congratulations! You have won the game!", 0xFFFFFF, NULL);
		DrawForegroundString(265, 318, "Press SPACE to reset.", 0xFFFFFF, NULL);
	}
}
