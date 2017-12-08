/* HeadMoveLeftAndDown.h - Gage O'Connor, October 2017 */

#include "Head_MoveLeftAndDown.h"
#include "Head_MoveFSM.h"

const HeadMoveLeftAndDown HeadMoveFSM::StateMoveLeftAndDown;

HeadMoveLeftAndDown::HeadMoveLeftAndDown()
{
	grabOffsets();
}
void HeadMoveLeftAndDown::Show() const
{
	std::cout << "MoveLeftAndDown";
}

void HeadMoveLeftAndDown::grabOffsets()
{
	for (int i = 0; i < Centipede::FRAMES_PER_MOVEMENT; i++)
	{
		offsets.push_back(sf::Vector3f(-float(Centipede::SPEED), 0, 0));
	}
}

const HeadMoveState* HeadMoveLeftAndDown::GetNextState(Centipede* chead) const
{
	const HeadMoveState *pNextState;
	Tile *pTile = chead->getTile();

	if (pTile->getLeft() != 0)
	{
		if (pTile->getLeft()->hasObject())
		{
			if (pTile->getLeft()->getObject()->getPoisonStatus() == true)
			{
				pNextState = &HeadMoveFSM::StatePoisonTurnRight;
				chead->setTile(pTile->getDown());
				//MainSprite.rotate(90);
			}
			else
			{
				pNextState = &HeadMoveFSM::StateTurnDownAndRight;
				chead->setTile(pTile->getDown());
			}
		}
		else
		{
			pNextState = &HeadMoveFSM::StateMoveLeftAndDown;
			chead->setTile(pTile->getLeft());
		}
	}
	else if (pTile->getDown() == 0)
	{
		pNextState = &HeadMoveFSM::StateTurnUpAndRight;
		chead->setTile(pTile->getUp());
		//isInPlayerArea = true;
	}
	else
	{
		pNextState = &HeadMoveFSM::StateTurnDownAndRight;
		chead->setTile(pTile->getDown());
	}
	return pNextState;
}