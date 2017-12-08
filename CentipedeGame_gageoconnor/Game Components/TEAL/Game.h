// Game.h
// Andre Berthiaume, June 2012
//
// Main game loop

#ifndef _Game
#define _Game

#include "GameClock.h"

class Game
{
private:
	static Game* gameInstance;			// Game set up as a singleton

	Game() { };								// Private constructor
	Game(const Game&) = delete;				// Prevent copy-construction
	Game& operator=(const Game&) = delete;	// Prevent assignment
	~Game() = default;						// Only this class can delete

	static Game& Instance()	    // Access reference (all public methods will be static)
	{
		if (! gameInstance) 
			gameInstance = new Game;
		return *gameInstance;
	};

	GameClock gameclock;

	void TerminateGame();

public:
	static const sf::Keyboard::Key KILLGAMEKEY;

	static void Run();

	static float TotalTime() { return Instance().gameclock.TotalTime(); };
	static float FrameTime() { return Instance().gameclock.FrameTime(); };
};

#endif _Game