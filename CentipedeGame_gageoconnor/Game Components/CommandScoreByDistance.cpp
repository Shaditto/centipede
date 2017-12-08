#include "CommandScoreByDistance.h"
#include "ScoreManager.h"

CommandScoreByDistance::CommandScoreByDistance(int val, int dist)
	: CommandScore(val), distance(dist)
{

}

void CommandScoreByDistance::Execute()
{
	CommandScore::Execute();
}