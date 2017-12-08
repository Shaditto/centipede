/* Level1.cpp - Gage O'Connor, October 2017 */

#include "Level1.h"
#include "FontWriter.h"
#include "Grid.h"
#include "CentralController.h"
#include "WaveManager.h"
#include "GlyphFactory.h"

#include "MushroomGrid.h"
#include "MushroomFactory.h"
#include "MushroomRegenFactory.h"

#include "PlayerManager.h"
#include "PlayerFactory.h"
#include "PlayerExplosionFactory.h"

#include "BulletFactory.h"
#include "bulletExplosionFactory.h"

#include "CentipedeSpawn.h"
#include "Centipede_HeadFactory.h"
#include "Centipede_SegmentFactory.h"

#include "ScorpionSpawn.h"
#include "ScorpionFactory.h"

#include "FleaSpawn.h"
#include "FleaFactory.h"

#include "SpiderSpawn.h"
#include "SpiderFactory.h"
#include "SpiderScoreFactory.h"

void Level1::Initialize()
{
	// Initial Startup
	WindowManager::SetBackgroundColor(sf::Color(0, 0, 0, 0));
	FontWriter::DisplayInfo();
	WaveManager::GrabWaves();

	// Creates the grid and controller
	pGrid = new Grid();
	pController = new CentralController(pGrid);

	// Gives Grid access to these
	WaveManager::SetGrid(pGrid);
	MushroomRegenFactory::setGrid(pGrid);
	PlayerManager::SetController(pController);

	pController->StartAI();

	// Collision Testing
	CollisionTestPair<Scorpion, Mushroom>();
	CollisionTestPair<Bullet, Scorpion>();
	CollisionTestPair<Bullet, CentipedeHead>();
	CollisionTestPair<Bullet, CentipedeSegment>();
	CollisionTestPair<Bullet, Mushroom>();
	CollisionTestPair<Bullet, Flea>();
	CollisionTestPair<Bullet, Spider>();
	CollisionTestPair<Bullet, Glyph>();
	CollisionTestPair<Player, Mushroom>();
	CollisionTestPair<Player, Spider>();
	CollisionTestPair<Player, CentipedeHead>();
	CollisionTestPair<Player, CentipedeSegment>();
	CollisionTestPair<Player, Flea>();
}

void Level1::Terminate()
{
	PlayerFactory::Terminate();
	PlayerExplosionFactory::Terminate();
	PlayerManager::Terminate(); // keep an eye on this >.>
	BulletFactory::Terminate();
	bulletExplosionFactory::Terminate();

	ScorpionSpawner::Terminate();
	ScorpionFactory::Terminate();

	FleaSpawner::Terminate();
	FleaFactory::Terminate();

	SpiderSpawner::Terminate();
	SpiderFactory::Terminate();
	SpiderScoreFactory::Terminate();

	MushroomFactory::Terminate();
	MushroomRegenFactory::Terminate();

	CentipedeSpawner::Terminate();
	CentipedeHeadFactory::Terminate();
	CentipedeSegmentFactory::Terminate();

	GlyphFactory::Terminate();
	FontWriter::Terminate();

	delete pGrid;
};