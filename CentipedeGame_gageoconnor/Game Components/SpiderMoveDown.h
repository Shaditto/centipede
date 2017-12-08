#ifndef _SpiderMoveDown
#define _SpiderMoveDownUp

#include "SpiderMoveState.h"

class SpiderMoveDown : public SpiderMoveState
{
public:
	SpiderMoveDown();
	virtual const SpiderMoveState* GetNextState(Spider *spider) const override;
	virtual void Show() const override;
};

#endif _SpiderMoveDown