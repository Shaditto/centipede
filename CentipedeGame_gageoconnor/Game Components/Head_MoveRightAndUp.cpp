/* HeadMoveRightAndUp.h - Gage O'Connor, October 2017 */

#include "Head_MoveRightAndUp.h"
#include "Head_MoveFSM.h"

const HeadMoveRightAndUp HeadMoveFSM::StateMoveRightAndUp;

HeadMoveRightAndUp::HeadMoveRightAndUp()
{
	grabOffsets();
}

void HeadMoveRightAndUp::Show() const
{
	std::cout << "MoveRightAndUp";
}

void HeadMoveRightAndUp::grabOffsets()
{
	for (int i = 0; i < Centipede::FRAMES_PER_MOVEMENT; i++)
	{
		offsets.push_back(sf::Vector3f(float(Centipede::SPEED), 0, 0));
	}
}

const HeadMoveState* HeadMoveRightAndUp::GetNextState(Centipede* chead) const
{
	const HeadMoveState *pNextState;
	Tile *pTile = chead->getTile();

	if (pTile->getRight() != 0) // Is a tile - not off screen
	{
		if (pTile->getRight()->hasObject())
		{
			if (pTile->getPos().y == 424) // We've reached upper-bounds
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
		if (pTile->getPos().y == 424)	 // We've reached upper-bounds
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