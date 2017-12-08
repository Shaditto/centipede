/* HeadMoveLeftAndUp.h - Gage O'Connor, October 2017 */

#include "Head_MoveLeftAndUp.h"
#include "Head_MoveFSM.h"

const HeadMoveLeftAndUp HeadMoveFSM::StateMoveLeftAndUp;

HeadMoveLeftAndUp::HeadMoveLeftAndUp()
{
	grabOffsets();
}

void HeadMoveLeftAndUp::Show() const
{
	std::cout << "MoveLeftAndUp";
}

void HeadMoveLeftAndUp::grabOffsets()
{
	for (int i = 0; i < Centipede::FRAMES_PER_MOVEMENT; i++)
	{
		offsets.push_back(sf::Vector3f(-float(Centipede::SPEED), 0, 0));
	}
}

const HeadMoveState* HeadMoveLeftAndUp::GetNextState(Centipede* chead) const
{
	const HeadMoveState *pNextState;
	Tile *pTile = chead->getTile();

	if (pTile->getLeft() != 0) // Is a tile - not off screen
	{
		if (pTile->getLeft()->hasObject())
		{
			if (pTile->getPos().y == 424.0f) // We've reached upper-bounds
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
		if (pTile->getPos().y == 424.0f)	 // We've reached upper-bounds
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
	return pNextState;
}