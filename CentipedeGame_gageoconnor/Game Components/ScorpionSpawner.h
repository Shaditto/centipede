/*ScorpionSpawner.h - Gage O'Connor, September 2017*/

#ifndef _ScorpionSpawner
#define _ScorpionSpawner

#include "TEAL\CommonElements.h"
#include "Grid.h"
#include "Scorpion.h"

class ScorpionSpawner
{
public:
	/*BIG FOUR*/
	ScorpionSpawner(Grid * Grid, float val);
	ScorpionSpawner(const ScorpionSpawner &) = default;
	ScorpionSpawner & operator =(const ScorpionSpawner &) = default;
	~ScorpionSpawner() = default;

	/*METHODS*/
	virtual void spawnOnLeft(Tile * tile);
	virtual void spawnOnRight(Tile* tile);

private:
	float H_SIZE;
	float SPAWN_AREA;
	int colLoc; //the col location to spawn a scorpion
};
#endif _ScorpionSpawner