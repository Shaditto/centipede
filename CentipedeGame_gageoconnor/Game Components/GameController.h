/* GameController.h - Gage O'Connor, October 2017 */

#ifndef _GameController
#define _GameController

#include "TEAL\CommonElements.h"

/* Set up as a Singleton*/
class GameController
{
public:
	static GameController *pInstance;	

	GameController();							 
	GameController(const GameController&) = delete;				// Prevents assignment			
	GameController& operator=(const GameController&) = delete;	// Only this can delete
	~GameController();

	static GameController& Instance() // Access reference (all public methods will be static)
	{
		if (!pInstance)
			pInstance = new GameController;
		return *pInstance;
	};

	/* Score Methods */
	void ResetScore();
	void AddScore(int val);
	int GetScore();

	void PlayerDies();

private:
	int score;
};
#endif _GameController