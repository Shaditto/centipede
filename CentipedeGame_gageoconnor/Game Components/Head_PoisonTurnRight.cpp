/* HeadPoisonTurnRight.h - Gage O'Connor, October 2017*/

#include "Head_PoisonTurnRight.h"
#include "Head_MoveFSM.h"

const HeadPoisonTurnRight HeadMoveFSM::StatePoisonTurnRight;

HeadPoisonTurnRight::HeadPoisonTurnRight()
{
	grabOffsets();
}

void HeadPoisonTurnRight::Show() const
{

}

void HeadPoisonTurnRight::grabOffsets()
{
	for (int i = 0; i < Centipede::FRAMES_PER_MOVEMENT; i++)
	{
		offsets.push_back(sf::Vector3f(0, float(Centipede::SPEED), 0));
	}
}

const HeadMoveState *HeadPoisonTurnRight::GetNextState(Centipede *chead) const
{
	const HeadMoveState *pNextState;
	Tile *pTile = chead->getTile();

	if (pTile->getDown() != 0)
	{
		pNextState = &HeadMoveFSM::StatePoisonTurnRight;
		chead->setTile(pTile->getDown());
	}
	else
	{
		pNextState = &HeadMoveFSM::StateMoveRightAndDown;
		chead->setTile(pTile->getRight());
		//MainSprite.rotate(90);
	}
	return pNextState;
}