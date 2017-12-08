#ifndef _SpiderMoveUp
#define _SpiderMoveUp

#include "SpiderMoveState.h"

class SpiderMoveUp : public SpiderMoveState
{
public:
	SpiderMoveUp();
	virtual const SpiderMoveState* GetNextState(Spider *spider) const override;
	virtual void Show() const override;
};

#endif _SpiderMoveUp
