#include "CommandScore.h"
#include "ScoreManager.h"

CommandScore::CommandScore(int val)
	: points(val)
{

}

void CommandScore::Execute()
{
	ScoreManager::AddScore(points);
}