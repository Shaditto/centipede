/* ScorpionFactory.h - Gage O'Connor, October 2017 */

#ifndef _ScorpionFactory
#define _ScorpionFactory

#include <stack>
#include "Scorpion.h"

// Forward Declaration
class CommandScore;
class CommandSoundLoop;

/* Set up as a Singleton*/
class ScorpionFactory
{
public:
	// Static services
	static void createScorpion(Grid *pGrid, float side, float speed) { Instance().privateCreateScorpion(pGrid, side, speed); };
	static void recycleScorpion(GameObject *scorpion) { Instance().privateRecycleScorpion(scorpion); };

	static void ReportDeath();	// Reporting death to ScoreManager
	static void PlaySound();	//
	static void PauseSound();	// Reporting sound to SoundManager

	static void Terminate();

private:
	static ScorpionFactory *pInstance;	// Set up as Singleton

	ScorpionFactory();
	ScorpionFactory(const ScorpionFactory &) = delete;					// Prevents copy-constructions
	ScorpionFactory & operator = (const ScorpionFactory &) = delete;	// Prevents assignment
	~ScorpionFactory();													// Only this can delete

	static ScorpionFactory & Instance() // Access reference (since all public methods will be static)
	{
		if (!pInstance)
			pInstance = new ScorpionFactory;
		return *pInstance;
	};

	std::stack<Scorpion *> recycledScorpions; // Non-static

	void privateCreateScorpion(Grid *pGrid, float side, float speed);
	void privateRecycleScorpion(GameObject *scorpion);

	CommandScore* pDeath;		// Reporting Scores
	CommandSoundLoop* pSound;	// Sound

	int spawnLoc;
	int counter;
};

#endif _ScorpionFactory
