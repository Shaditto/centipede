/* AttractorInput.h - Gage O'Connor, October 2017 */

#ifndef _Attractor
#define _Attractor

#include "TEAL\CommonElements.h"
#include "Input.h"
#include "AttractorMovement.h"

// Forward declaration
class Player;

class AttractorInput : public Input
{
public:
	AttractorInput();
	//virtual void KeyPressed(sf::Attractor::Key k, bool altKey, bool ctrlKey, bool shiftKey, bool systemKey);

	/* METHODS */
	virtual void Update();
	virtual void AssignPlayer(Player* player);
	virtual void checkMove();
	virtual void checkEdges();

	// Actual Movement
	virtual void MoveDiagRightUp();
	virtual void MoveDiagRightDown();
	virtual void MoveDiagLeftUp();
	virtual void MoveDiagLeftDown();

private:
	Player *pPlayer;

	const sf::Vector2f X_CLAMP;
	const sf::Vector2f Y_CLAMP;

	sf::Vector2f oldPos;

	AttractorMovement currentMove;
	AttractorMovement oldMove;
};
#endif _Input

