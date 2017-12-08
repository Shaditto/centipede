/* SpiderSpawner.h - Gage O'Connor, October 2017 */

#ifndef _SpiderSpawner
#define _SpiderSpawner

#include "Spider.h"
#include "SpiderFactory.h"

/* Set up as a Singleton */
class SpiderSpawner
{
public:
	// Static services
	static void SpawnSpider() { Instance().privateSpawnSpider(); };
	static void SetGrid(Grid* pGrid) { Instance().privateSetGrid(pGrid); };
	static void SetActive(bool isActive) { Instance().privateSetActive(isActive); };

	static void Terminate();
private:
	static SpiderSpawner* pInstance; // Set up as Singleton

	SpiderSpawner();
	SpiderSpawner(const SpiderSpawner &) = delete;					// Prevents copy-constructions
	SpiderSpawner & operator = (const SpiderSpawner &) = delete;		// Prevents assignment
	~SpiderSpawner() = default;											// Only this can delete

	static SpiderSpawner & Instance() // Access reference (since all public methods will be static)
	{
		if (!pInstance)
			pInstance = new SpiderSpawner;
		return *pInstance;
	};

	void privateSpawnSpider();
	void privateSetGrid(Grid* pGrid);
	void privateSetActive(bool isActive);

	Grid* pGrid;
	const float left;
	const float right;
	const int SPAWN_CHANCE = 10;
	const int CHANCE = 5;

	int side;
	bool isActive;
};

#endif _SpiderSpawner
