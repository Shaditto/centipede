/* SpiderFactory.h - Gage O'Connor, October 2017 */

#ifndef _SpiderFactory
#define _SpiderFactory

#include <stack>
#include "Spider.h"

// Forward Declarations
class CommandScoreByDistance;
class CommandSoundLoop;

/* Set up as a Singleton*/
class SpiderFactory
{
public:
	// Static services
	static void createSpider(Grid *pGrid, float side) { Instance().privateCreateSpider(pGrid, side); };
	static void recycleSpider(GameObject *spider) { Instance().privateRecycleSpider(spider); };

	// Update score
	static void ReportSpiderDeath(int dist);

	static void PlaySound();	//
	static void PauseSound();	// Reporting sound to SoundManager

	static void Terminate();

private:
	static SpiderFactory *pInstance;	// Set up as Singleton

	SpiderFactory();
	SpiderFactory(const SpiderFactory &) = delete;					// Prevents copy-constructions
	SpiderFactory & operator = (const SpiderFactory &) = delete;	// Prevents assignment
	~SpiderFactory();												// Only this can delete

	static SpiderFactory & Instance() // Access reference (since all public methods will be static)
	{
		if (!pInstance)
			pInstance = new SpiderFactory;
		return *pInstance;
	};

	std::stack<Spider *> recycledSpiders; // Non-static

	void privateCreateSpider(Grid *pGrid, float side);
	void privateRecycleSpider(GameObject *spider);
	void privateReportSpiderDeath(int dist);

	// Update score
	CommandScoreByDistance* pDeathClose;
	CommandScoreByDistance* pDeathMedium;
	CommandScoreByDistance* pDeathFar;

	// Sound
	CommandSoundLoop* pSound;

	const int spawnLoc = 28;
	const int LEFT_SIDE = 0;
	const int RIGHT_SIDE = 29;
	int counter;
};

#endif _SpiderFactory