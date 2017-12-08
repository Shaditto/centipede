/* HeadMoveRightAndUp.h - Gage O'Connor, October 2017 */
#ifndef _HeadTurnUpAndRight
#define _HeadTurnUpAndRight

#include "Head_MoveState.h"

class HeadTurnUpAndRight : public  HeadMoveState
{
public:
	HeadTurnUpAndRight();
	std::vector<sf::Vector3f> GetMoveOffsets() const override { return offsets; }
	virtual const HeadMoveState* GetNextState(Centipede* chead) const override;
	virtual void Show() const override;

private:
	void grabOffsets();
	std::vector<sf::Vector3f> offsets;
	const float BORDER = 424.0f;
};

#endif _HeadTurnUpAndRight

