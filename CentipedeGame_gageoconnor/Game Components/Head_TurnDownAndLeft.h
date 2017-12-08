/* HeadMoveLeftAndDown.h - Gage O'Connor, October 2017 */
#ifndef _HeadTurnDownAndLeft
#define _HeadTurnDownAndLeft

#include "Head_MoveState.h"

class HeadTurnDownAndLeft : public  HeadMoveState
{
public:
	HeadTurnDownAndLeft();
	std::vector<sf::Vector3f> GetMoveOffsets() const override { return offsets; }
	virtual const HeadMoveState* GetNextState(Centipede* chead) const override;
	virtual void Show() const override;

private:
	void grabOffsets();
	std::vector<sf::Vector3f> offsets;
};

#endif _HeadTurnDownAndLeft