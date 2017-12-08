/* CentipedeSpawner.h - Gage O'Connor, October 2017 */

#ifndef _CentipedeSpawner
#define _CentipedeSpawner

#include "Centipede.h"
#include "Centipede_HeadFactory.h"

/* Set up as a Singleton */
class CentipedeSpawner
{
public:
	// Static services
	static void SpawnCentipede(Tile* pTile, int num) { Instance().privateSpawnCentipede(pTile, num); };

	static void Terminate();
private:
	static CentipedeSpawner* pInstance; // Set up as Singleton

	CentipedeSpawner();
	CentipedeSpawner(const CentipedeSpawner &) = delete;					// Prevents copy-constructions
	CentipedeSpawner & operator = (const CentipedeSpawner &) = delete;		// Prevents assignment
	~CentipedeSpawner() = default;											// Only this can delete

	static CentipedeSpawner & Instance() // Access reference (since all public methods will be static)
	{
		if (!pInstance)
			pInstance = new CentipedeSpawner;
		return *pInstance;
	};

	void privateSpawnCentipede(Tile* pTile, int num);

	const int SPAWN_CHANCE = 10;
	const int CHANCE = 5;

	int direction;
};

#endif _CentipedeSpawner