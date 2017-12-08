/*FleaSpawner.h - Gage O'Connor, September 2017*/

#ifndef _FleaSpawner
#define _FleaSpawner

#include "TEAL\CommonElements.h"
#include "Grid.h"
#include "Flea.h"

class FleaSpawner
{
public:
	/*BIG FOUR*/
	FleaSpawner(Grid * Grid);
	FleaSpawner(const FleaSpawner &) = default;
	FleaSpawner & operator =(const FleaSpawner &) = default;
	~FleaSpawner() = default;

	/*METHODS*/
	virtual void spawnFlea(Tile * tile);

private:
	float W_SIZE;
	int rowLoc; //the row location to spawn a scorpion
};
#endif _FleaSpawner
