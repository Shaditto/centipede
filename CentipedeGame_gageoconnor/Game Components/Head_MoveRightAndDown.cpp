/* HeadMoveRightAndDown.h - Gage O'Connor, October 2017 */

#include "Head_MoveRightAndDown.h"
#include "Head_MoveFSM.h"

const HeadMoveRightAndDown HeadMoveFSM::StateMoveRightAndDown;

HeadMoveRightAndDown::HeadMoveRightAndDown()
{
	grabOffsets();
}
void HeadMoveRightAndDown::Show() const
{
	std::cout << "MoveRightAndDown";
}

void HeadMoveRightAndDown::grabOffsets()
{
	for (int i = 0; i < Centipede::FRAMES_PER_MOVEMENT; i++)
	{
		offsets.push_back(sf::Vector3f(float(Centipede::SPEED), 0, 0));
	}
}

const HeadMoveState* HeadMoveRightAndDown::GetNextState(Centipede* chead) const
{
	const HeadMoveState *pNextState;
	Tile *pTile = chead->getTile();

	if (pTile->getRight() != 0)
	{
		if (pTile->getRight()->hasObject())
		{
			if (pTile->getRight()->getObject()->getPoisonStatus() == true)
			{
				pNextState = &HeadMoveFSM::StatePoisonTurnLeft;
				chead->setTile(pTile->getDown());
				//MainSprite.rotate(90);
			}
			else
			{
				pNextState = &HeadMoveFSM::StateTurnDownAndLeft;
				chead->setTile(pTile->getDown());
			}
		}
		else
		{
			pNextState = &HeadMoveFSM::StateMoveRightAndDown;
			chead->setTile(pTile->getRight());
		}
	}
	else if (pTile->getDown() == 0)
	{
		pNextState = &HeadMoveFSM::StateTurnUpAndLeft;
		chead->setTile(pTile->getUp());
		//isInPlayerArea = true;
	}
	else
	{
		pNextState = &HeadMoveFSM::StateTurnDownAndLeft;
		chead->setTile(pTile->getDown());
	}
	return pNextState;
}