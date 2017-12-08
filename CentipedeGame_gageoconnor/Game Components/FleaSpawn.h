/* FleaSpawner.h - Gage O'Connor, October 2017 */

#ifndef _FleaSpawner
#define _FleaSpawner

#include "Flea.h"
#include "FleaFactory.h"

/* Set up as a Singleton */
class FleaSpawner
{
public:
	// Static services
	static void SetActive(bool isActive) { Instance().privateSetActive(isActive); };
	static void SetFlea(bool isFlea) { Instance().privateSetFlea(isFlea); };
	static void SetNumShroom(float numShroom) { Instance().privateSetNumShroom(numShroom); };
	static void SetGrid(Grid* pGrid) { Instance().privateSetGrid(pGrid); };
	static void UpdateMushroomCount(int val) { Instance().privateUpdateMushroomCount(val); };

	static void Terminate();
private:
	static FleaSpawner* pInstance; // Set up as Singleton

	FleaSpawner();
	FleaSpawner(const FleaSpawner &) = delete;						// Prevents copy-constructions
	FleaSpawner & operator = (const FleaSpawner &) = delete;		// Prevents assignment
	~FleaSpawner() = default;										// Only this can delete

	static FleaSpawner & Instance() // Access reference (since all public methods will be static)
	{
		if (!pInstance)
			pInstance = new FleaSpawner;
		return *pInstance;
	};

	void privateSpawnFlea();
	void privateSetActive(bool isActive);
	void privateSetFlea(bool isFlea);
	void privateSetNumShroom(float numShroom);
	void privateSetGrid(Grid* pGrid);
	void privateUpdateMushroomCount(int val);

	Grid* pGrid;

	float numShrooms;		// Number of shrooms required in Player Area
	int numShroomsActive;	// Number of mushrooms in Player Area
	bool isActive;			// Do we need to spawn Flea'
	bool isFlea;			// Is there a flea already active
};

#endif _FleaSpawner