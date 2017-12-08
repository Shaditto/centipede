/* CentralController.h - Gage O'Connor, October 2017 */

#include "CentralController.h"

#include "PlayerManager.h"
#include "SoundManager.h"
#include "ScoreManager.h"
#include "WaveManager.h"

#include "MushroomRegenFactory.h"
#include "FontWriter.h"

#include "CentipedeSpawn.h"
#include "FleaFactory.h"
#include "ScorpionSpawn.h"
#include "SpiderSpawn.h"

#include "Head_MoveFSM.h"


CentralController::CentralController(Grid* pGrid)
{
	this->pGrid = pGrid;
	RegisterInput(InputFlags::KeyPressed);
}

void CentralController::Update()
{
	// Proccesses Sound and Score requests
	ScoreManager::ProcessScores();
	SoundManager::ProcessSounds();
	SoundManager::PauseSounds();
}

void CentralController::KeyPressed(sf::Keyboard::Key k, bool altKey, bool ctrlKey, bool shiftKey, bool systemKey)
{
	if (k == sf::Keyboard::Num1)	//P1 Mode
	{
		// Initialize P1
		PlayerManager::ResetP1();
		WaveManager::ResetFirstCritters();

		// Reset and Create the Grid
		pGrid->ResetGrid();
		pGrid->CreateMushroomGrid();
		pGrid->CreatePlayerAreaMushroomGrid();

		// Reset the Waves
		WaveManager::ProcessFirstWave();
	}
	else if ((k == sf::Keyboard::Num2))	// Testing Mode
	{
		// Initialize P1
		PlayerManager::ResetP1();
		WaveManager::ResetFirstCritters();

		// Reset and Create the Grid
		pGrid->ResetGrid();
		pGrid->CreateMushroomGrid();
		//pGrid->CreatePlayerAreaMushroomGrid();
	}

	/* FOR TESTING...SPAWNING */
	if (k == sf::Keyboard::Numpad1)
	{
		ScorpionSpawner::SpawnScorpion(100);	// 1 - Scorpion on left
	}
	else if (k == sf::Keyboard::Numpad2)
	{
		FleaFactory::createFlea(this->pGrid);			// 2 - Flea
	}
	else if (k == sf::Keyboard::Numpad3)
	{
		SpiderSpawner::SpawnSpider();	// 3 - Scorpion on right
	}
	else if (k == sf::Keyboard::Numpad5)
	{
		// 5 - Centipede Head and one segment
		CentipedeSpawner::SpawnCentipede(pGrid->getArr(24, 9), 0);
		return;
	}
	else if (k == sf::Keyboard::Numpad8)
	{
		CentipedeSpawner::SpawnCentipede(pGrid->getArr(24, 9), 5);
		return;
	}
}

void CentralController::StartAI()
{
	pGrid->ResetGrid();
	FontWriter::DisplayHighScores(pGrid->getArr(START_X, START_Y));

	// Create initial mushroom field
	pGrid->CreateMushroomGrid();
	pGrid->CreatePlayerAreaMushroomGrid();

	// Create Attractor
	PlayerManager::CreateP1(pGrid);

	WaveManager::ProcessFirstWave();
}

void CentralController::RestartAI()
{
	// Create initial mushroom field
	pGrid->ResetGrid();

	FontWriter::DisplayInfo();
	FontWriter::DisplayHighScores(pGrid->getArr(START_X, START_Y));
	pGrid->CreateMushroomGrid();
	pGrid->CreatePlayerAreaMushroomGrid();

	WaveManager::ProcessFirstWave();
}

CentralController::~CentralController()
{
}