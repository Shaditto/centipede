/* CommandScore.h - Gage O'Connor, October 2017 */

#ifndef _CommandScore
#define _CommandScore

#include "CommandBase.h"

class CommandScore : public CommandBase
{
public: 
	CommandScore() = delete;
	CommandScore(int val);

	virtual void Execute() override;

protected:
	int points; // Points to add to Score
};

#endif _CommandScore