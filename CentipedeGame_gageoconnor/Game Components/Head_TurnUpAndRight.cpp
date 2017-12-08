/* HeadTurnUpAndRight.h - Gage O'Connor, October 2017 */

#include "Head_TurnUpAndRight.h"
#include "Head_MoveFSM.h"

const HeadTurnUpAndRight HeadMoveFSM::StateTurnUpAndRight;

HeadTurnUpAndRight::HeadTurnUpAndRight()
{
	grabOffsets();
}
void HeadTurnUpAndRight::Show() const
{
	std::cout << "TurnUpAndRight";
}

void HeadTurnUpAndRight::grabOffsets()
{
		offsets.push_back(sf::Vector3f(-3.061f, -0.609f, -22.5f));
		offsets.push_back(sf::Vector3f(-2.569f, -1.734f, -22.5f));
		offsets.push_back(sf::Vector3f(-1.734f, -2.569f, -22.5f));
		offsets.push_back(sf::Vector3f(-0.609f, -3.061f, -22.5f));
		offsets.push_back(sf::Vector3f(0.609f, -3.061f, -22.5f));
		offsets.push_back(sf::Vector3f(1.734f, -2.569f, -22.5f));
		offsets.push_back(sf::Vector3f(2.569f, -1.734f, -22.5f));
		offsets.push_back(sf::Vector3f(3.061f, -0.609f, -22.5f));
}

const HeadMoveState* HeadTurnUpAndRight::GetNextState(Centipede* chead) const
{
	const HeadMoveState *pNextState;
	Tile *pTile = chead->getTile();

	if (pTile->getRight() != 0) // Is a tile - not off screen
	{
		if (pTile->getRight()->hasObject())
		{
			if (pTile->getPos().y == BORDER) // We've reached upper-bounds
			{
				pNextState = &HeadMoveFSM::StateTurnDownAndLeft;
				chead->setTile(pTile->getDown());
			}
			else						 // Can keep moving up
			{
				pNextState = &HeadMoveFSM::StateTurnUpAndLeft;
				chead->setTile(pTile->getUp());
			}
		}
		else							 // Keep moving right
		{
			pNextState = &HeadMoveFSM::StateMoveRightAndUp;
			chead->setTile(pTile->getRight());
		}
	}
	else if (pTile->getUp() != 0)		 // We've reached right-edge
	{
		if (pTile->getPos().y == BORDER)	 // We've reached upper-bounds
			{
				pNextState = &HeadMoveFSM::StateTurnDownAndLeft;
				chead->setTile(pTile->getDown());
			}
			else						 // Can keep moving up
			{
				pNextState = &HeadMoveFSM::StateTurnUpAndLeft;
				chead->setTile(pTile->getUp());
			}
	}
	return pNextState;
}