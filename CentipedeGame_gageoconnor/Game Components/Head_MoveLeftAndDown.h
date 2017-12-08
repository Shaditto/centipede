/* HeadMoveLeftAndDown.h - Gage O'Connor, October 2017 */
#ifndef _HeadMoveLeftAndDown
#define _HeadMoveLeftAndDown

#include "Head_MoveState.h"

class HeadMoveLeftAndDown : public HeadMoveState
{
public:
	HeadMoveLeftAndDown();
	std::vector<sf::Vector3f> GetMoveOffsets() const override { return offsets; }
	virtual const HeadMoveState* GetNextState(Centipede* chead) const override;
	virtual void Show() const override;

private:
	void grabOffsets();
	std::vector<sf::Vector3f> offsets;
};

#endif _HeadMoveLeftAndDown