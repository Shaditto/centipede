// LoadAllResources.cpp
// Andre Berthiaume, June 2012
//
// The user fills the method with all resources that need loading

#include "ResourceManager.h"
#include "../Splash.h"

void ResourceManager::LoadAllResources()
{
	SetStartScene(new Splash());

	// Preloads textures
	AddTexture("blaster", "blaster.png");
	AddTexture("death", "death.png");
	AddTexture("bullet", "bullet.png");
	AddTexture("mushroom", "mushroom.png");
	AddTexture("tile", "tile.png");
	AddTexture("scorpion", "scorpion.png");
	AddTexture("flea", "flea.png");
	AddTexture("centipede_head", "centipede_head.png");
	AddTexture("centipede_segment", "centipede_segment.png");
	AddTexture("centipede_body", "centipede_body.png");
	AddTexture("spider", "spider.png");
	AddTexture("spiderScore", "spiderScore.png");
	AddTexture("spawn", "spawn.png");

	// Preload sounds
	AddSound("fire1", "fire1.wav");
	AddSound("scorpion_new", "scorpion_new.wav");
	AddSound("flea_new", "flea_new.wav");
	AddSound("spider_new", "spider_new.wav");
	AddSound("beat", "beat.wav");
	AddSound("death", "death.wav");
	AddSound("bonus", "bonus.wav");

	// Preload Fonts
	AddTexture("Alphabet", "FONTwPLAYER.bmp");
}