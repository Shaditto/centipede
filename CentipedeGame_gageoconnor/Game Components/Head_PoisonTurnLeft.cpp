/* HeadPoisonTurnLeft.h - Gage O'Connor, October 2017*/

#include "Head_PoisonTurnLeft.h"
#include "Head_MoveFSM.h"

const HeadPoisonTurnLeft HeadMoveFSM::StatePoisonTurnLeft;

HeadPoisonTurnLeft::HeadPoisonTurnLeft()
{
	grabOffsets();
}

void HeadPoisonTurnLeft::Show() const
{

}

void HeadPoisonTurnLeft::grabOffsets()
{
	for (int i = 0; i < Centipede::FRAMES_PER_MOVEMENT; i++)
	{
		offsets.push_back(sf::Vector3f(0, float(Centipede::SPEED), 0));
	}
}

const HeadMoveState *HeadPoisonTurnLeft::GetNextState(Centipede *chead) const
{
	const HeadMoveState *pNextState;
	Tile *pTile = chead->getTile();

	if (pTile->getDown() != 0)
	{
		pNextState = &HeadMoveFSM::StatePoisonTurnLeft;
		chead->setTile(pTile->getDown());
	}
	else
	{
		pNextState = &HeadMoveFSM::StateMoveLeftAndDown;
		chead->setTile(pTile->getLeft());
		//MainSprite.rotate(90);
	}
	return pNextState;
}