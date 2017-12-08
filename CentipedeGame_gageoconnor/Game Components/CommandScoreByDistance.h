/* CommandScoreByDistance.h - Gage O'Connor, October 2017 */

#ifndef _CommandScoreByDistance
#define _CommandScoreByDistance

#include "CommandScore.h"

class CommandScoreByDistance : public CommandScore
{
public:
	CommandScoreByDistance() = delete;
	CommandScoreByDistance(int val, int dist);

	int GetDistance() { return distance; }

	virtual void Execute() override;

private:
	int distance;
};

#endif _CommandScore
