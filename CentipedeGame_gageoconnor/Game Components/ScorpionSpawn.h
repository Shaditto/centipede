/* ScorpionSpawner.h - Gage O'Connor, October 2017 */

#ifndef _ScorpionSpawner
#define _ScorpionSpawner

#include "Scorpion.h"
#include "ScorpionFactory.h"

/* Set up as a Singleton */
class ScorpionSpawner
{
public:
	// Static services
	static void SpawnScorpion(float speed) { Instance().privateSpawnScorpion(speed); };
	static void SetGrid(Grid* pGrid) { Instance().privateSetGrid(pGrid); };
	static void SetActive(bool isActive) { Instance().privateSetActive(isActive); };

	static void Terminate();
private:
	static ScorpionSpawner* pInstance; // Set up as Singleton

	ScorpionSpawner();
	ScorpionSpawner(const ScorpionSpawner &) = delete;					// Prevents copy-constructions
	ScorpionSpawner & operator = (const ScorpionSpawner &) = delete;		// Prevents assignment
	~ScorpionSpawner() = default;											// Only this can delete

	static ScorpionSpawner & Instance() // Access reference (since all public methods will be static)
	{
		if (!pInstance)
			pInstance = new ScorpionSpawner;
		return *pInstance;
	};

	void privateSpawnScorpion(float speed);
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

#endif _ScorpionSpawner