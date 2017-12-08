/* WaveManager.h - Gage O'Connor, October 2017 */

#ifndef _WaveManager
#define _WaveManager

#include "TEAL\CommonElements.h"
#include "WaveData.h"

#include <iostream>
#include <fstream>
#include "Grid.h"

// Forward Declaration
class Centipede;
class Scorpion;
class Spider;
class Flea;

/* Set up as a Singleton */
class WaveManager : public GameObject
{
public:
	// Static services
	static void GrabWaves() { Instance().privateGrabWaves(); };

	static void ProcessFirstWave() { Instance().privateProcessFirstWave(); }
	static void ProcessWave() { Instance().privateProcessWave(); };
	static void ProcessNextWave() { Instance().privateProcessNextWave(); };

	static void SetGrid(Grid* pGrid) { Instance().privateSetGrid(pGrid); };
	static void ResetCritters() { Instance().privateResetCritters(); };
	static void ResetFirstCritters() { Instance().privateResetFirstCritters(); };

	static void SetCenti(Centipede* pHead) { Instance().privateSetCenti(pHead); }
	static void FreeCenti(Centipede* pHead) { Instance().privateFreeCenti(pHead); }

	static void SetFlea(Flea* pFlea) { Instance().privateSetFlea(pFlea); }
	static void FreeFlea(Flea* pFlea) { Instance().privateFreeFlea(pFlea); }

	static void SetScorp(Scorpion* pScorp) { Instance().privateSetScorp(pScorp); }
	static void FreeScorp(Scorpion* pScorp) { Instance().privateFreeScorp(pScorp); }

	static void SetSpider(Spider* pSpider) { Instance().privateSetSpider(pSpider); }
	static void FreeSpider(Spider* pSpider) { Instance().privateFreeSpider(pSpider); }

	static void Terminate();

private:
	static WaveManager* pInstance; // Set up as Singleton

	WaveManager();
	WaveManager(const WaveManager &) = delete;						// Prevents copy-constructions
	WaveManager & operator = (const WaveManager &) = delete;		// Prevents assignment
	~WaveManager() = default;										// Only this can delete

	static WaveManager & Instance() // Access reference (since all public methods will be static)
	{
		if (!pInstance)
			pInstance = new WaveManager;
		return *pInstance;
	};

	virtual void Alarm0();
	virtual void Alarm1();

	void privateGrabWaves();
	void privateProcessFirstWave();
	void privateProcessWave();
	void privateProcessNextWave();
	void privateSetGrid(Grid* pGrid);
	void privateResetCritters();
	void privateResetFirstCritters();

	void privateSetCenti(Centipede* centi);
	void privateSetFlea(Flea* pFlea);
	void privateSetScorp(Scorpion* pScorp);
	void privateSetSpider(Spider* pSpider);

	void privateFreeCenti(Centipede* centi);
	void privateFreeFlea(Flea* pFlea);
	void privateFreeScorp(Scorpion* pScorp);
	void privateFreeSpider(Spider* pSpider);

	const float WAVE_SIZE = 1.0f;

	const int numOfWaves;
	const int CENTI_LOC = 14;
	Grid* pGrid;

	std::list<Centipede*> pCentiHeads;
	Scorpion* pScorp;
	Spider* pSpider;
	Flea* pFlea;

	WaveData data;

	int index;
	int test = -1;
};

#endif _WaveManager