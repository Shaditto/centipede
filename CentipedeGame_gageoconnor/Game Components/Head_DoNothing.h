/* HeadDoNothing.h - Gage O'Connor, October 2017 */
#ifndef _HeadDoNothing
#define _HeadDoNothing

#include "Head_MoveState.h"

class HeadDoNothing : public  HeadMoveState
{
public:
	HeadDoNothing();
	std::vector<sf::Vector3f> GetMoveOffsets() const override { return offsets; }
	virtual const HeadMoveState* GetNextState(Centipede* chead) const override {return 0;};
	virtual void Show() const override;

private:
	void grabOffsets();
	std::vector<sf::Vector3f> offsets;
};

#endif _HeadDoNothing

