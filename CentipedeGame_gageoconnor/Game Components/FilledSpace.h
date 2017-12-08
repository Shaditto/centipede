/* FilledSpace.h - Gage O'Connor, October 2017 */

#ifndef _FilledSpace
#define _FilledSpace

#include "TEAL\CommonElements.h"
#include "Tile.h"

class FilledSpace : public GameObject
{
public:
	virtual void restoreHealth() {};
	virtual void setPoison() {};
	const bool virtual getPoisonStatus() { return 0; };
	const int virtual getHealth() { return 0; };
	const int virtual getMaxHealth() { return 0; };
};

#endif _FilledSpace
