/* ScoreManager.h - Gage O'Connor, October 2017 */

#ifndef _ScoreManager
#define _ScoreManager

#include <stack>

// Forward Declarations
class CommandScore;
class CommandScoreByDistance;

class ScoreManager
{
public:
	// Score Events
	enum class ScoreEvents { CentipedeHeadDeath, CentipedeSegmentDeath, FleaDeath, ScorpionDeath, MushroomDeath, MushroomPoisonDeath, MushroomRegenerate };
	enum class ScoreDistanceEvents {SpiderDeathClose, SpiderDeathMedium, SpiderDeathFar };

	static void AddScore(int val);

	static CommandScore* GetScoreCommand(ScoreEvents event);
	static CommandScoreByDistance* GetScoreCommand(ScoreDistanceEvents event);

	static void SendScoreCommand(CommandScore * command);
	static void ProcessScores();

private:
	// Score Values
	static const int CentipedeHeadDeath = 100;
	static const int CentipedeSegmentDeath = 10;

	static const int FleaDeath = 200;
	static const int ScorpionDeath = 1000;

	static const int MushroomDeath = 1;
	static const int MushroomPoisonDeath = 5;
	static const int MushroomRegenerate = 5;

	static const int SpiderDeathClose = 900;
	static const int SpiderDistanceClose = 10;

	static const int SpiderDeathMedium = 600;
	static const int SpiderDistanceMedium = 20;

	static const int SpiderDeathFar = 300;
	static const int SpiderDistanceFar = 30;

	std::stack<CommandScore *> StackCommand;

	static ScoreManager* pInstance;

	static ScoreManager& Instance()	// Access reference (all public methods will be static)
	{
		if (!pInstance)
			pInstance = new ScoreManager;
		return *pInstance;
	};

	void privateProcessScore();
};

#endif _ScoreManager