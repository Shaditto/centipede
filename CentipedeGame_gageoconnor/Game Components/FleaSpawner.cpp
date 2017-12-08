/*FleaSpawner.cpp - Gage O'Connor, September 2017*/

#include "FleaSpawner.h"

FleaSpawner::FleaSpawner(Grid * grid)
{
	//get screen width
	W_SIZE = WindowManager::MainWindow.getView().getSize().x / 16.0f;

	//choose a random tile based on width
	rowLoc = rand() % static_cast<int>(W_SIZE);

	//spawn flea at that location
	spawnFlea(grid->getArr(0, rowLoc));
}

void FleaSpawner::spawnFlea(Tile * tile)
{
	new Flea();
}