/* PlayerManager.h - Gage O'Connor, October 2017*/

#ifndef _PlayerManager
#define _PlayerManager

#include "TEAL\CommonElements.h"
#include "KeyBoardInput.h"
#include "AttractorInput.h"
#include "CentralController.h"

// Forward Declarations
class Player;
class Grid;

/* Set up as a Singleton */
class PlayerManager
{
public:

	/* METHODS */
	static void CreateP1(Grid* pGrid);
	static void Respawn();
	static void ResetP1();
	static void ResetAI();
	static void DestroyCurrPlayer();
	static void Swap();
	static void AddScore(int val) { Instance().privateAddScore(val); };
	static void SubtractLife() { Instance().privateSubtractLife(); };
	static void SetController(CentralController* pControl);

	static Player* GetCurrPlayer();

	static void Terminate();

	//virtual void Alarm0();

private:
	static PlayerManager *pInstance;

	PlayerManager();
	PlayerManager(const PlayerManager &) = delete;						// Prevents copy-constructions
	PlayerManager & operator = (const PlayerManager &) = delete;		// Prevents assignment
	~PlayerManager() = default;											// Only this can delete

	static PlayerManager& Instance() // Access reference (since all public methods will be static)
	{
		if (!pInstance)
			pInstance = new PlayerManager();
		return *pInstance;
	};

	Player* pCurrPlayer;
	Player* pPlayerOne;
	Player* pPlayerAI;

	KeyboardInput* pKeyboard;
	AttractorInput* pAttractor;

	CentralController* pController;

	Grid* pGrid;

	int currPlayer;
	int currLife;
	int currScore;

	void privateAddScore(int val);
	void privateSubtractLife();
};

#endif _PlayerManager

