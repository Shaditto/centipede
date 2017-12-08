/* KeyboardInput.h - Gage O'Connor, October 2017 */

#ifndef _Keyboard
#define _Keyboard

#include "TEAL\CommonElements.h"
#include "Input.h"

// Forward declaration
class Player;

class KeyboardInput : public Input
{
public:
	KeyboardInput();
	//virtual void KeyPressed(sf::Keyboard::Key k, bool altKey, bool ctrlKey, bool shiftKey, bool systemKey);

	/* METHODS */
	virtual void Update();
	virtual void AssignPlayer(Player* player);

private:
	Player *pPlayer;
};
#endif _Input
