/*SplashController.cpp - Gage O'Connor, September 2017*/

#include "SplashController.h"
#include "Level1.h"

SplashController::SplashController()
{
	//assigns texture
	//SplashSprite = sf::Sprite(ResourceManager::GetTexture("Splashpage"));
	
	RegisterInput(InputFlags::KeyPressed);
}

SplashController::~SplashController()
{
	DeregisterInput();
}

void SplashController::Draw()
{
	//draws texture to screen
	WindowManager::MainWindow.draw(SplashSprite);
}

void SplashController::KeyPressed(sf::Keyboard::Key k, bool altKey, bool ctrlKey, bool shiftKey, bool systemKey)
{
	//loads Level1 upon keypress
	SceneManager::ChangeScene(new Level1);
}