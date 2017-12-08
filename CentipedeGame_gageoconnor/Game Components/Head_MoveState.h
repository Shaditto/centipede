/* HeadMoveState.h - Gage O'Connor, October 2017 */

#ifndef _HeadMoveState
#define _HeadMoveState

#include "CentipedeHead.h"

class HeadMoveState
{
public:
	HeadMoveState() {};
	virtual std::vector<sf::Vector3f> GetMoveOffsets() const { return MyMoveOffsets; }
	virtual const HeadMoveState* GetNextState(Centipede* chead) const = 0;
	virtual void Show() const = 0;;


protected:
	const std::vector<sf::Vector3f> MyMoveOffsets;
	const std::vector<float> MyRotationOffsets;
};

#endif _HeadMoveState