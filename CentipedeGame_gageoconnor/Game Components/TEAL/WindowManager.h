// WindowManager.h
// Andre Berthiaume, June 2012
//
// General Window controls and settings
// (Future versions will include View managements as well)

#ifndef _WINDOWING_H
#define _WINDOWING_H

#include "SFML\Graphics.hpp"

class WindowManager                  
{
private:
	static WindowManager* windowInstance;			// Setting up a singleton
	WindowManager();								// Private constructor
	WindowManager( const WindowManager&);			// Prevent copy construction
	WindowManager& operator=(const WindowManager&);	// prevent assignment
	static WindowManager& Instance()  
	{
		if (! windowInstance) 
			windowInstance = new WindowManager;
		return *windowInstance;
	};

	void SetTitle(){MainWindow.setTitle(windowCaption + ": " + captionMsg); };

	int windowWidth;
	int windowHeight;
	std::string windowCaption;	
	sf::Color backgroundColor;
	std::string captionMsg;

public:
	static sf::RenderWindow MainWindow;	
	
	static void Initialize();
	static void Terminate();
	static void Clear();
	static void Display();
	static void SetCaptionName(std::string name){ Instance().windowCaption = name; Instance().SetTitle();  };
	static void SetCaptionMessage(std::string msg){ Instance().captionMsg = msg; Instance().SetTitle();  };

	static void SetBackgroundColor(sf::Color col){ Instance().backgroundColor = col; };

	/// \brief Returns the mouse position in window coordinates.
	/// 
	/// \return A <a href="http://www.sfml-dev.org/documentation/2.0/classsf_1_1Vector2.php">sf::Vector2f</a> of the coordinates	
	/// 
	/// Typically used in the GameObject::Update. For exameple:
	/// 
	///		\code
	///		void Object1::Update()
	///		{
	///			sf::Vector2f pos =  WindowManager::MousePosition();
	///			 
	///			< Do something with pos, like move a sprite or shape. >
	///		}
	///		\endcode
	static sf::Vector2f MousePosition(){ return static_cast<sf::Vector2f>( sf::Mouse::getPosition( WindowManager::MainWindow )); }
};

#endif _WINDOWING_H