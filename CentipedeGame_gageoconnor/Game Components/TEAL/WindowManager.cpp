// WindowManager.cpp
// Andre Berthiaume, June 2012
//
// General Window controls and settings
// (Future versions will include View managements as well)

#include "WindowManager.h"

WindowManager* WindowManager::windowInstance = NULL;

sf::RenderWindow WindowManager::MainWindow;

WindowManager::WindowManager()
{
	windowWidth = 480; //720
	windowHeight = 512; //768
	windowCaption = "TEAL/SFML";
	backgroundColor = sf::Color(0,64,64); 
	captionMsg = "";
}

void WindowManager::Initialize()
{
	WindowManager::MainWindow.create( sf::VideoMode( Instance().windowWidth, Instance().windowHeight), Instance().windowCaption + ": " + Instance().captionMsg );
	WindowManager::MainWindow.setKeyRepeatEnabled(false);
	WindowManager::MainWindow.setFramerateLimit(60);
	WindowManager::MainWindow.setMouseCursorVisible(false);
}

void WindowManager::Terminate()
{
	delete windowInstance;
}

void WindowManager::Clear()
{
	WindowManager::MainWindow.clear(Instance().backgroundColor);
}

void WindowManager::Display()
{
	WindowManager::MainWindow.display();
}



