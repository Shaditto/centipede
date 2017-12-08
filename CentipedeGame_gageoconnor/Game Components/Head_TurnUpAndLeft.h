/* HeadMoveLeftAndUp.h - Gage O'Connor, October 2017 */
#ifndef _HeadTurnUpAndLeft
#define _HeadTurnUpAndLeft

#include "Head_MoveState.h"

class HeadTurnUpAndLeft : public  HeadMoveState
{
public:
	HeadTurnUpAndLeft();
	std::vector<sf::Vector3f> GetMoveOffsets() const override { return offsets; }
	virtual const HeadMoveState* GetNextState(Centipede* chead) const override;
	virtual void Show() const override;

private:
	void grabOffsets();
	std::vector<sf::Vector3f> offsets;
	const float BORDER = 424.0f;
};

#endif _HeadTurnUpAndLeft
