/* HeadMoveRightAndDown.h - Gage O'Connor, October 2017 */
#ifndef _HeadMoveRightAndDown
#define _HeadMoveRightAndDown

#include "Head_MoveState.h"

class HeadMoveRightAndDown : public HeadMoveState
{
public:
	HeadMoveRightAndDown();
	std::vector<sf::Vector3f> GetMoveOffsets() const override { return offsets; }
	virtual const HeadMoveState* GetNextState(Centipede* chead) const override;
	virtual void Show() const override;
private:
	void grabOffsets();
	std::vector<sf::Vector3f> offsets;
};

#endif _HeadMoveRightAndDown