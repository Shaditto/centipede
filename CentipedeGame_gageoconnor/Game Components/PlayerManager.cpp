/* PlayerManager.cpp - Gage O'Connor, October 2017*/

#include "PlayerManager.h"

#include "Player.h"
#include "PlayerFactory.h"
#include "FontWriter.h"
#include "CentralController.h"

PlayerManager* PlayerManager::pInstance= nullptr;

PlayerManager::PlayerManager()
{
	pCurrPlayer = nullptr;
	pPlayerOne = nullptr;
	pPlayerAI = nullptr;
	pGrid = nullptr;
	pController = nullptr;

	pKeyboard = new KeyboardInput();
	pAttractor = new AttractorInput();

	currPlayer = 0;
	currLife = 3;
}

void PlayerManager::privateAddScore(int val)
{
	// Displays score in appropriate location
	if (Instance().pCurrPlayer == Instance().pPlayerOne)
	{
		// Adds score to Player 1
		Instance().pCurrPlayer->setScore(val);
		FontWriter::ComputeP1Score(Tools::ToString(Instance().pCurrPlayer->getScore()), Instance().pCurrPlayer->getScore());
		//ConsoleMsg::WriteLine("Current Score: " + Tools::ToString(Instance().pCurrPlayer->getScore()) + "\n");
	}
}

void PlayerManager::privateSubtractLife()
{
	// Update current Player1 Lives
	if (Instance().pCurrPlayer == Instance().pPlayerOne && Instance().currLife != 0)
		Instance().currLife--;

	if (Instance().pCurrPlayer == Instance().pPlayerOne && (Instance().currLife) <= 0)
	{
		Instance().Swap();
		Instance().pController->RestartAI();
		
	}
	
	ConsoleMsg::WriteLine("Current Lives: " + Tools::ToString(Instance().currLife) + "\n");

	// Displays remaining lives in appropriate location
	if (Instance().pCurrPlayer == Instance().pPlayerOne)
		FontWriter::ComputeP1Lives(Tools::ToString(Instance().currLife));
}

// Sets Player 1
void PlayerManager::CreateP1(Grid* pGrid)
{
	Instance().pGrid = pGrid;
	Instance().pPlayerAI = PlayerFactory::createPlayer(Instance().pGrid);
	Instance().pCurrPlayer = Instance().pPlayerAI;
	ConsoleMsg::WriteLine("CURRENT PLAYER: AI ");

	// Assigns Input to player
	Instance().pAttractor->AssignPlayer(Instance().pCurrPlayer);

	Instance().currPlayer = 0;
}

void PlayerManager::Respawn()
{
	// Respawns P1
	// Creates P1 instance
	//Instance().pCurrPlayer = PlayerFactory::createPlayer(Instance().pGrid);

	if (Instance().currPlayer == 1) // Swap to Player 1
	{
		// Creates P1 instance
		Instance().pPlayerOne = PlayerFactory::createPlayer(Instance().pGrid);
		Instance().pCurrPlayer = Instance().pPlayerOne;

		// Adjusts input mode
		Instance().pKeyboard->AssignPlayer(Instance().pCurrPlayer);
		Instance().pAttractor->AssignPlayer(0);

		// Adds score to Player 1
		Instance().pCurrPlayer->setScore(Instance().currScore);
		FontWriter::ComputeP1Score(Tools::ToString(Instance().pCurrPlayer->getScore()), Instance().pCurrPlayer->getScore());
		ConsoleMsg::WriteLine("Current Score: " + Tools::ToString(Instance().pCurrPlayer->getScore()) + "\n");
	}
	else if (Instance().currPlayer == 0) // Swap back to AI
	{
		// Creates AI instance
		Instance().pPlayerAI = PlayerFactory::createPlayer(Instance().pGrid);
		Instance().pCurrPlayer = Instance().pPlayerAI;

		// Adjusts input mode
		Instance().pKeyboard->AssignPlayer(0);
		Instance().pAttractor->AssignPlayer(Instance().pCurrPlayer);
	}

	//Instance().pCurrPlayer->resetPosition(sf::Vector2f(232, 472));

	ConsoleMsg::WriteLine("Respawned ");
	WaveManager::ProcessWave();
}

void PlayerManager::Swap()
{
	if (Instance().currPlayer == 0) // Swap to Player 1
	{
		Instance().ResetP1();
	}
	else if (Instance().currPlayer == 1) // Swap back to AI
	{
		Instance().ResetAI();
	}
}

void PlayerManager::ResetP1()
{
	// Creates P1 instance
	Instance().pPlayerOne = PlayerFactory::createPlayer(Instance().pGrid);
	Instance().pCurrPlayer = Instance().pPlayerOne;

	Instance().pPlayerAI->MarkForDestroy();
	ConsoleMsg::WriteLine("SWAPPED: Player 1 Active ");

	// Adjusts input mode
	Instance().pKeyboard->AssignPlayer(Instance().pCurrPlayer);
	Instance().pAttractor->AssignPlayer(0);

	// Resets score
	FontWriter::ComputeP1Score(Tools::ToString(Instance().pCurrPlayer->getScore()), Instance().pCurrPlayer->getScore());
	Instance().currPlayer = 1;
	Instance().currLife = 3;

	ConsoleMsg::WriteLine("Current Lives: " + Tools::ToString(Instance().currLife) + "\n");
}

void PlayerManager::DestroyCurrPlayer()
{
	if (Instance().pCurrPlayer == Instance().pPlayerOne)
		Instance().currScore = Instance().pCurrPlayer->getScore();

	Instance().pCurrPlayer->MarkForDestroy();

	Instance().pKeyboard->AssignPlayer(0);
	Instance().pAttractor->AssignPlayer(0);
}

void PlayerManager::ResetAI()
{
	// Creates AI instance
	Instance().pPlayerAI = PlayerFactory::createPlayer(Instance().pGrid);
	Instance().pCurrPlayer = Instance().pPlayerAI;

	// Removes P1 instance
	Instance().pPlayerOne->MarkForDestroy();
	ConsoleMsg::WriteLine("SWAPPED: Player AI Active ");

	// Adjusts input mode
	Instance().pKeyboard->AssignPlayer(0);
	Instance().pAttractor->AssignPlayer(Instance().pCurrPlayer);

	// Resets score
	FontWriter::ComputeP1Score(Tools::ToString(Instance().pCurrPlayer->getScore()), Instance().pCurrPlayer->getScore());

	Instance().currPlayer = 0;
}

void PlayerManager::SetController(CentralController* pControl)
{
	Instance().pController = pControl;
}

Player* PlayerManager::GetCurrPlayer()
{
	return Instance().pCurrPlayer;
}

void PlayerManager::Terminate()
{
	delete pInstance;
	pInstance = nullptr;
}
