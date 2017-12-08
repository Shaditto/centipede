/* FleaFactory.h - Gage O'Connor, October 2017 */

#ifndef _FleaFactory
#define _FleaFactory

#include <stack>
#include "Flea.h"

// Forward Declaration
class CommandScore;
class CommandSound;

/* Set up as a Singleton*/
class FleaFactory
{
public:
	// Static services
	static void createFlea(Grid *pGrid) { Instance().privateCreateFlea(pGrid); };
	static void recycleFlea(GameObject *flea) { Instance().privateRecycleFlea(flea); };

	static void ReportDeath();	// Reporting death to ScoreManager
	static void PlaySound();	// Reporting sound to SoundManager

	static void Terminate();

private:
	static FleaFactory *pInstance;	// Set up as Singleton

	FleaFactory();
	FleaFactory(const FleaFactory &) = delete;					// Prevents copy-constructions
	FleaFactory& operator = (const FleaFactory &) = delete;	// Prevents assignment
	~FleaFactory();												// Only this can delete

	static FleaFactory& Instance() // Access reference (since all public methods will be static)
	{
		if (!pInstance)
			pInstance = new FleaFactory;
		return *pInstance;
	};

	std::stack<Flea*> recycledFleas; // Non-static

	void privateCreateFlea(Grid* pGrid);
	void privateRecycleFlea(GameObject* flea);

	CommandScore* pDeath;	// Reporting Scores
	CommandSound* pSound;	// Sound

	const int RAND_CHANCE = 30;
	const int SPAWN_LOC = 1;
	int spawnLoc;
};

#endif _FleaFactory
