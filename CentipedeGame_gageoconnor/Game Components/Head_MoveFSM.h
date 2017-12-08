#include "Head_DoNothing.h"
#include "Head_MoveRightAndDown.h"
#include "Head_MoveRightAndUp.h"
#include "Head_MoveLeftAndDown.h"
#include "Head_MoveLeftAndUp.h"
#include "Head_TurnDownAndLeft.h"
#include "Head_TurnDownAndRight.h"
#include "Head_TurnUpAndLeft.h"
#include "Head_TurnUpAndRight.h"
#include "Head_PoisonTurnLeft.h"
#include "Head_PoisonTurnRight.h"

class HeadMoveFSM
{
private:

public:
	// Static const references to all of the states
	static const HeadDoNothing StateDoNothing;
	static const HeadMoveRightAndDown StateMoveRightAndDown;
	static const HeadMoveRightAndUp StateMoveRightAndUp;
	static const HeadMoveLeftAndDown StateMoveLeftAndDown;
	static const HeadMoveLeftAndUp StateMoveLeftAndUp;
	static const HeadTurnDownAndLeft StateTurnDownAndLeft;
	static const HeadTurnDownAndRight StateTurnDownAndRight;
	static const HeadTurnUpAndLeft StateTurnUpAndLeft;
	static const HeadTurnUpAndRight StateTurnUpAndRight;
	static const HeadPoisonTurnLeft StatePoisonTurnLeft;
	static const HeadPoisonTurnRight StatePoisonTurnRight;
};
