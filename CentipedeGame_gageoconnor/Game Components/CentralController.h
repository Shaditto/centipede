/* CentralController.h - Gage O'Connor, October 2017 */

#ifndef _CentralController
#define _CentralController

#include "TEAL\CommonElements.h"

// Forward Declarations
class Grid;

class CentralController : public GameObject
{
public:
	CentralController(Grid* pGrid);
	~CentralController();

	/* METHODS */
	virtual void Update();
	virtual void KeyPressed(sf::Keyboard::Key k, bool altKey, bool ctrlKey, bool shiftKey, bool systemKey);
	virtual void StartAI();
	virtual void RestartAI();

private:
	Grid* pGrid;

	const int START_X = 2;
	const int START_Y = 9;
};

#endif _CentralController