/* HeadTurnDownAndLeft.h - Gage O'Connor, October 2017 */

#include "Head_TurnDownAndLeft.h"
#include "Head_MoveFSM.h"

const HeadTurnDownAndLeft HeadMoveFSM::StateTurnDownAndLeft;

HeadTurnDownAndLeft::HeadTurnDownAndLeft()
{
	grabOffsets();
}
void HeadTurnDownAndLeft::Show() const
{
	std::cout << "TurnDownAndLeft";
}

void HeadTurnDownAndLeft::grabOffsets()
{
		offsets.push_back(sf::Vector3f(3.061f, 0.609f, 22.5f));
		offsets.push_back(sf::Vector3f(2.569f, 1.734f, 22.5f));
		offsets.push_back(sf::Vector3f(1.734f, 2.569f, 22.5f));
		offsets.push_back(sf::Vector3f(0.609f, 3.061f, 22.5f));
		offsets.push_back(sf::Vector3f(-0.609f, 3.061f, 22.5f));
		offsets.push_back(sf::Vector3f(-1.734f, 2.569f, 22.5f));
		offsets.push_back(sf::Vector3f(-2.569f, 1.734f, 22.5f));
		offsets.push_back(sf::Vector3f(-3.061f, 0.609f, 22.5f));
}

const HeadMoveState* HeadTurnDownAndLeft::GetNextState(Centipede* chead) const
{
	const HeadMoveState *pNextState;
	Tile *pTile = chead->getTile();

	if (pTile->getLeft() != 0)
	{
		if (pTile->getLeft()->hasObject())
		{
			if (pTile->getLeft()->getObject()->getPoisonStatus() == true)
			{
				pNextState = &HeadMoveFSM::StatePoisonTurnLeft;
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