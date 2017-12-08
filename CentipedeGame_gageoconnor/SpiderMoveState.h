/* SpiderMoveState.h - Gage O'Connor, October 2017 */
#ifndef _SpiderMoveState
#define _SpiderMoveState

#include "Game Components\Spider.h"

class SpiderMoveState
{
public:
	SpiderMoveState() {};
	virtual const SpiderMoveState* GetNextState(Spider *spider) const = 0;
	virtual void Show() const = 0;
};
#endif _SpiderMoveState
