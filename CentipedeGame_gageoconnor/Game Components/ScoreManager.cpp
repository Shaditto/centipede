/* ScoreManager.h - Gage O'Connor, October 2017 */

#include "ScoreManager.h"

#include "TEAL/CommonElements.h"
#include "CommandScore.h"
#include "CommandScoreByDistance.h"

#include "PlayerManager.h"

ScoreManager* ScoreManager::pInstance = nullptr;

CommandScore* ScoreManager::GetScoreCommand(ScoreEvents event)
{
	CommandScore* pCommand = nullptr;

	switch (event)
	{
	case ScoreEvents::CentipedeHeadDeath:
		pCommand = new CommandScore(CentipedeHeadDeath);
		break;
	case ScoreEvents::CentipedeSegmentDeath:
		pCommand = new CommandScore(CentipedeSegmentDeath);
		break;
	case ScoreEvents::FleaDeath:
		pCommand = new CommandScore(FleaDeath);
		break;
	case ScoreEvents::ScorpionDeath:
		pCommand = new CommandScore(ScorpionDeath);
		break;
	case ScoreEvents::MushroomDeath:
		pCommand = new CommandScore(MushroomDeath);
		break;
	case ScoreEvents::MushroomPoisonDeath:
		pCommand = new CommandScore(MushroomPoisonDeath);
		break;
	case ScoreEvents::MushroomRegenerate:
		pCommand = new CommandScore(MushroomRegenerate);
		break;
	default:
		break;
	}

	return pCommand;
}

CommandScoreByDistance* ScoreManager::GetScoreCommand(ScoreDistanceEvents event)
{
	CommandScoreByDistance* pCommand = nullptr;

	switch (event)
	{
	case ScoreDistanceEvents::SpiderDeathClose:
		pCommand = new CommandScoreByDistance(SpiderDeathClose, SpiderDistanceClose);
		break;
	case ScoreDistanceEvents::SpiderDeathMedium:
		pCommand = new CommandScoreByDistance(SpiderDeathMedium, SpiderDistanceMedium);
		break;
	case ScoreDistanceEvents::SpiderDeathFar:
		pCommand = new CommandScoreByDistance(SpiderDeathFar, SpiderDistanceFar);
		break;
	default:
		break;
	}

	return pCommand;
}

void ScoreManager::AddScore(int val)
{
	ConsoleMsg::WriteLine("Adding Score: " + Tools::ToString(val));
  	PlayerManager::AddScore(val);
}

void ScoreManager::SendScoreCommand(CommandScore* command)
{
	Instance().StackCommand.push(command);
}

void ScoreManager::ProcessScores()
{
	Instance().privateProcessScore();
}

void ScoreManager::privateProcessScore()
{
	CommandScore* pCommand;

	while (!StackCommand.empty())
	{
		pCommand = StackCommand.top();
		pCommand->Execute();

		StackCommand.pop();
	}
}