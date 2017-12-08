// ResouceManager.cpp
// Andre Berthiaume, June 2012
//
// Overall resource manager

#include "ResourceManager.h"
#include "SceneManager.h"
#include "ConsoleMsg.h"
#include "TEALShow.h"

using namespace std;

ResourceManager* ResourceManager::resmgrInstance = NULL;

std::string ResourceManager::GetBasePath(){ return Instance().Resource_Path; }

ResourceManager::ResourceManager()
{
	Resource_Path = "resources/";
}

void ResourceManager::UnloadAllResources()
{
	delete resmgrInstance;
}

void ResourceManager::SetBasePath(std::string path)
{ 
	if ( path[ path.length() - 1] != '/' ) path = path + "/";
	Instance().Resource_Path = path; 
}

void ResourceManager::AddImage(std::string resKey, string path)
{
	AddItem<sf::Image>( Instance().CollectionImage, path, resKey);
}

sf::Image& ResourceManager::GetImage( std::string resKey )
{
	return GetItem<sf::Image>( Instance().CollectionImage, resKey);
}

void ResourceManager::AddSound(std::string resKey, std::string path)
{
	AddItem<sf::SoundBuffer>( Instance().CollectionSoundBuffer, path, resKey);
}

sf::SoundBuffer& ResourceManager::GetSound(std::string resKey)
{
	return GetItem<sf::SoundBuffer>( Instance().CollectionSoundBuffer, resKey);
}

void ResourceManager::AddFont( std::string resKey, std::string path )
{
	AddItem<sf::Font>( Instance().CollectionFont, path, resKey);
}

sf::Font& ResourceManager::GetFont( std::string resKey )
{
	return GetItem<sf::Font>( Instance().CollectionFont, resKey);
}

void ResourceManager::AddMusic(std::string resKey, std::string path)
{
	// NOTE: We can't use the AddItem method because sf::Music does NOT have loadFromFile...
	std::map< std::string, sf::Music*>::iterator it =  Instance().CollectionMusic.find(resKey);
	//*
	if ( it != Instance().CollectionMusic.end() )
		ConsoleMsg::ShowError("Using resource key '" + resKey + "' multiple times for the same resource type.");
	else
	{
		sf::Music *musicPtr = new sf::Music;
		if ( !( musicPtr->openFromFile( Instance().Resource_Path + path)  ) )
			ConsoleMsg::ShowError("Failed to load resource key " + resKey + "' (" + path + ")");
		else
		{
			Instance().CollectionMusic[resKey] = musicPtr;
			ConsoleMsg::ShowStatus("Resource key '" + resKey + "' (" + path + ") successfully loaded");
		}
	}
	//*/
}

sf::Music* ResourceManager::GetMusic(std::string resKey)
{
	return GetItem<sf::Music*>( Instance().CollectionMusic, resKey);
}

void ResourceManager::AddTexture(std::string resKey, string path, bool CreateBitmap)
{
	AddItem<sf::Texture>(  Instance().CollectionTexture, path, resKey);

	// automatically add the bitmap.
	if ( CreateBitmap )
		Instance().CollectionBitmap[resKey] = CollisionTools::ContructTextureBitmap( Instance().CollectionTexture[resKey].copyToImage() );

}

sf::Texture& ResourceManager::GetTexture( std::string resKey )
{
	return GetItem<sf::Texture>( Instance().CollectionTexture, resKey);
}

CollisionTools::TextureBitmap& ResourceManager::GetTextureBitmap( std::string resKey)
{
	return GetItem<CollisionTools::TextureBitmap>( Instance().CollectionBitmap, resKey);
}

void ResourceManager::SetSpriteTextureAndBitmap( std::string resKey, sf::Sprite &s, CollisionTools::TextureBitmap &b)
{
	s.setTexture( GetTexture(resKey) );
	b = GetTextureBitmap( resKey );
}


void ResourceManager::SetStartScene( Scene* sc){ SceneManager::SetStartScene(sc); }