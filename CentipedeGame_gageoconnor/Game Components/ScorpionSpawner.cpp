/*ScorpionSpawner.cpp - Gage O'Connor, September 2017*/

#include "ScorpionSpawner.h"

ScorpionSpawner::ScorpionSpawner(Grid * grid, float val)
{
	H_SIZE = WindowManager::MainWindow.getView().getSize().y / 16.0f;
	SPAWN_AREA = H_SIZE - 6.0f;

	colLoc = rand() % static_cast<int>(SPAWN_AREA);

	//spawn on left side
	if (val > 0)
	{
		spawnOnLeft(grid->getArr(colLoc, 0));
	}
	//spawn on right side
	else
	{
		spawnOnRight(grid->getArr(colLoc, 29));
	}
}

/*METHODS*/
void ScorpionSpawner::spawnOnLeft(Tile * tile)
{
}
void ScorpionSpawner::spawnOnRight(Tile* tile)
{

}