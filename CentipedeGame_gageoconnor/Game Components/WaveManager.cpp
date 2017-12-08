/* WaveManager.cpp - Gage O'Connor, October 2017 */

#include "WaveManager.h"

#include "PlayerManager.h"
#include "CentipedeSpawn.h"
#include "FleaSpawn.h"
#include "ScorpionSpawn.h"
#include "SpiderSpawn.h"

WaveManager* WaveManager::pInstance = nullptr;

WaveManager::WaveManager()
	: numOfWaves(3)
{
	pGrid = 0;
	index = 0;

	pScorp = 0;
	pSpider = 0;
	pFlea = 0;
}

void WaveManager::privateGrabWaves()
{
	std::ifstream inFile;
	std::string line;
	std::string tmp;

	float val = 0;

	inFile.open("waves.txt"); // Attempt to open waves.txt
	if (!inFile)
	{
		ConsoleMsg::WriteLine("Unable to Open file!");
		exit(1);
	}
	// Grabs Text File line-by-line, and then Compares String to parameters and assigns value appropriately
	while (std::getline(inFile, line))
	{
		std::stringstream ss(line);

		if (line.find("Wave") != std::string::npos)
		{
			ss >> tmp >> val;
			data.currentWave.push_back(val);
		}
		else if  (line.find("CENTIPEDE") != std::string::npos)
		{
			if (line.find("Length") != std::string::npos)
			{
				ss >> tmp >> val;
				data.centiLength.push_back(val);
			}
			else if (line.find("Speed") != std::string::npos)
			{
				ss >> tmp >> val;
				data.centiSpeed.push_back(val);
			}
			else if (line.find("Heads") != std::string::npos)
			{
				ss >> tmp >> val;
				data.centiHeads.push_back(val);
			}
		}
		else if (line.find("FLEA") != std::string::npos)
		{
			if (line.find("Present") != std::string::npos)
			{
				ss >> tmp >> val;
				data.fleaPresent.push_back(val);
			}
			else if (line.find("Trigger") != std::string::npos)
			{
				ss >> tmp >> val;
				data.fleaRate.push_back(val);
			}
		}
		else if (line.find("SCORPION") != std::string::npos)
		{
			if (line.find("Present") != std::string::npos)
			{
				ss >> tmp >> val;
				data.scorpPresent.push_back(val);
			}
			else if (line.find("Frequency") != std::string::npos)
			{
				ss >> tmp >> val;
				data.scorpRate.push_back(val);
			}
			else if (line.find("Speed") != std::string::npos)
			{
				ss >> tmp >> val;
				data.scorpSpeed.push_back(val);
			}
		}
		else if (line.find("SPIDER") != std::string::npos)
		{
			if (line.find("Present") != std::string::npos)
			{
				ss >> tmp >> val;
				data.spiderPresent.push_back(val);
			}
			else if (line.find("Frequency") != std::string::npos)
			{
				ss >> tmp >> val;
				data.spiderRate.push_back(val);
			}
			else if (line.find("Speed") != std::string::npos)
			{
				ss >> tmp >> val;
				data.spiderSpeed.push_back(val);
			}
		}
	}
	inFile.close();
}

void WaveManager::privateProcessFirstWave()
{
	//Resets wave to beginning
	index = 0;

	// Go to wave
	Instance().ProcessWave();
}

void WaveManager::privateProcessWave()
{
	// Spawns Centipede
	CentipedeSpawner::SpawnCentipede(pGrid->getArr(1, CENTI_LOC), int(data.centiLength[index]));

	// Sets up Flea data
	FleaSpawner::SetGrid(pGrid);
	FleaSpawner::SetActive(data.fleaPresent[index]);
	FleaSpawner::SetNumShroom(data.fleaRate[index]);
	
	// Sets up Scorpion data
	ScorpionSpawner::SetGrid(pGrid);
	ScorpionSpawner::SetActive(data.scorpPresent[index]);
	SetAlarm(0, data.scorpRate[index]);

	// Sets up Spider data
	SpiderSpawner::SetGrid(pGrid);
	SpiderSpawner::SetActive(data.spiderPresent[index]);
	SetAlarm(1, data.spiderRate[index]);

	//ConsoleMsg::WriteLine("Current Wave: " + Tools::ToString(data.currentWave[index]));
}

void WaveManager::privateProcessNextWave()
{
	// Increments to next wave if available
	if (index + 1 <= data.currentWave.size() - WAVE_SIZE)
	{
		index++;
	}

	// Go to next wave
	Instance().ProcessWave();
}

void WaveManager::privateResetCritters()
{
	if (pScorp != 0)
	{
		pScorp->MarkForDestroy();
		pScorp = 0;
	}

	if (pFlea != 0)
	{
		pFlea->MarkForDestroy();
		pFlea = 0;
	}

	if (pSpider != 0)
	{
		pSpider->MarkForDestroy();
		pSpider = 0;
	}

	while (Instance().pCentiHeads.size() != 0)
	{
		Instance().pCentiHeads.front()->ReportHeadRecall();
		Instance().pCentiHeads.front()->MarkForDestroy();

	}

	// Regens Mushrooms
	Instance().pGrid->FindDamagedShrooms();
	Instance().pGrid->RegenMushrooms();
}

void WaveManager::privateResetFirstCritters()
{
	if (pScorp != 0)
	{
		pScorp->MarkForDestroy();
		pScorp = 0;
	}

	if (pFlea != 0)
	{
		pFlea->MarkForDestroy();
		pFlea = 0;
	}

	if (pSpider != 0)
	{
		pSpider->MarkForDestroy();
		pSpider = 0;
	}

	while (Instance().pCentiHeads.size() != 0)
	{
		Instance().pCentiHeads.front()->ReportHeadRecall();
		Instance().pCentiHeads.front()->MarkForDestroy();
	}
}

void WaveManager::Alarm0()
{
	//ConsoleMsg::WriteLine("Scorpion Initial Alarm: " + Tools::ToString(Game::FrameTime));

	// If a Critter is not already on screen
	if (Instance().pScorp == 0)
		ScorpionSpawner::SpawnScorpion(data.scorpSpeed[index]);

	// Resets Alarm Time
	SetAlarm(0, data.scorpRate[index]);
}

void WaveManager::Alarm1()
{
	// If a Critter is not already on screen
	if (Instance().pSpider == 0)
		SpiderSpawner::SpawnSpider();

		
	// Resets Alarm Time
	SetAlarm(1, data.spiderRate[index]);
}

void WaveManager::privateSetGrid(Grid* pGrid)
{
	// Assigns Grid
	this->pGrid = pGrid;
}

void WaveManager::Terminate()
{
	delete pInstance;
	pInstance = nullptr;
}

void WaveManager::privateSetCenti(Centipede* centi)
{
	if (centi != nullptr)
		Instance().pCentiHeads.push_back(centi);
}

void WaveManager::privateSetFlea(Flea* pFlea)
{
	if (pFlea != nullptr)
	{
		Instance().pFlea = pFlea;
	}
}

void WaveManager::privateSetScorp(Scorpion* pScorp)
{
	if (pScorp != nullptr)
	{
		Instance().pScorp = pScorp;
	}
}

void WaveManager::privateSetSpider(Spider* pSpider)
{
	if (pSpider != nullptr)
	{
		Instance().pSpider = pSpider;
	}
}

void WaveManager::privateFreeCenti(Centipede* pCenti)
{
	if (pCenti != nullptr && Instance().pCentiHeads.size() != 0 && Instance().test == -1)
	{
		Instance().pCentiHeads.remove(pCenti);
	}
}

void WaveManager::privateFreeFlea(Flea* pFlea)
{
	if (pFlea != nullptr)
		Instance().pFlea = nullptr;
}

void WaveManager::privateFreeScorp(Scorpion* pScorp)
{
	if (pScorp != nullptr)
		Instance().pScorp = nullptr;
}

void WaveManager::privateFreeSpider(Spider* pSpider)
{
	if (pSpider != nullptr)
		Instance().pSpider = nullptr;
}