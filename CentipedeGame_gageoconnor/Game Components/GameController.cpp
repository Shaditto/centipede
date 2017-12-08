/* GameController.cpp - Gage O'Connor, October 2017 */

#include "GameController.h"

GameController* GameController::pInstance;

GameController::GameController()
{
	ResetScore();
	ConsoleMsg::WriteLine("Current Score: " + Tools::ToString(score));
}

void GameController::ResetScore()
{
	score = 0;
}

void GameController::AddScore(int val)
{
	score += val;
	ConsoleMsg::WriteLine("Current Score: " + Tools::ToString(score));
}

int GameController::GetScore()
{
	return score;
}

void GameController::PlayerDies()
{
}