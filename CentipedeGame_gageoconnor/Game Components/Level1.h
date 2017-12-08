/* Level1.h - Gage O'Connor, September 2017 */

#ifndef _Level1
#define _Level1

#include "TEAL\CommonElements.h"

// Forward declarations
class Grid;
class CentralController;

class Level1 : public Scene
{
public:
	virtual void Initialize();
	virtual void Terminate();

private: 
	Grid* pGrid;
	CentralController* pController;
};
#endif _Level1