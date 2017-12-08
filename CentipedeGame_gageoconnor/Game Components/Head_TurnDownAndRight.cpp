/* HeadTurnDownAndRight.h - Gage O'Connor, October 2017 */

#include "Head_TurnDownAndRight.h"
#include "Head_MoveFSM.h"

const HeadTurnDownAndRight HeadMoveFSM::StateTurnDownAndRight;

HeadTurnDownAndRight::HeadTurnDownAndRight()
{
	grabOffsets();
}

void HeadTurnDownAndRight::Show() const
{
	std::cout << "TurnDownAndRight";
}

void HeadTurnDownAndRight::grabOffsets()
{
	// Calculate turning offsets
		offsets.push_back(sf::Vector3f(-3.061f, 0.609f, -22.5f));
		offsets.push_back(sf::Vector3f(-2.569f, 1.734f, -22.5f));
		offsets.push_back(sf::Vector3f(-1.734f, 2.569f, -22.5f));
		offsets.push_back(sf::Vector3f(-0.609f, 3.061f, -22.5f));
		offsets.push_back(sf::Vector3f(0.609f, 3.061f, -22.5f));
		offsets.push_back(sf::Vector3f(1.734f, 2.569f, -22.5f));
		offsets.push_back(sf::Vector3f(2.569f, 1.734f, -22.5f));
		offsets.push_back(sf::Vector3f(3.061f, 0.609f, -22.5f));
}

const HeadMoveState* HeadTurnDownAndRight::GetNextState(Centipede* chead) const
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