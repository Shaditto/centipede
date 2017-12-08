/* HeadTurnUpAndLeft.h - Gage O'Connor, October 2017 */

#include "Head_TurnUpAndLeft.h"
#include "Head_MoveFSM.h"

const HeadTurnUpAndLeft HeadMoveFSM::StateTurnUpAndLeft;

HeadTurnUpAndLeft::HeadTurnUpAndLeft()
{
	grabOffsets();
}
void HeadTurnUpAndLeft::Show() const
{
	std::cout << "TurnUpAndLeft";
}

void HeadTurnUpAndLeft::grabOffsets()
{
		offsets.push_back(sf::Vector3f(3.061f, -0.609f, 22.5f));
		offsets.push_back(sf::Vector3f(2.569f, -1.734f, 22.5f));
		offsets.push_back(sf::Vector3f(1.734f, -2.569f, 22.5f));
		offsets.push_back(sf::Vector3f(0.609f, -3.061f, 22.5f));
		offsets.push_back(sf::Vector3f(-0.609f, -3.061f, 22.5f));
		offsets.push_back(sf::Vector3f(-1.734f, -2.569f, 22.5f));
		offsets.push_back(sf::Vector3f(-2.569f, -1.734f, 22.5f));
		offsets.push_back(sf::Vector3f(-3.061f, -0.609f, 22.5f));
}

const HeadMoveState* HeadTurnUpAndLeft::GetNextState(Centipede* chead) const
{
	const HeadMoveState *pNextState;
	Tile *pTile = chead->getTile();

	if (pTile->getLeft() != 0) // Is a tile - not off screen
	{
		if (pTile->getLeft()->hasObject())
		{
			if (pTile->getPos().y == BORDER) // We've reached upper-bounds
			{
				pNextState = &HeadMoveFSM::StateTurnDownAndRight;
				chead->setTile(pTile->getDown());
			}
			else						 // Can keep moving up
			{
				pNextState = &HeadMoveFSM::StateTurnUpAndRight;
				chead->setTile(pTile->getUp());
			}
		}
		else							 // Keep moving right
		{
			pNextState = &HeadMoveFSM::StateMoveLeftAndUp;
			chead->setTile(pTile->getLeft());
		}
	}
	else if (pTile->getUp() != 0)		 // We've reached right-edge
	{
		if (pTile->getPos().y == BORDER) // We've reached upper-bounds
		{
			pNextState = &HeadMoveFSM::StateTurnDownAndRight;
			chead->setTile(pTile->getDown());
		}	
		else							// Can keep moving up
		{
			pNextState = &HeadMoveFSM::StateTurnUpAndRight;
			chead->setTile(pTile->getUp());
		}
	}
	return pNextState;
}