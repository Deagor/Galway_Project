#include "stdafx.h"
#include "LevelManager.h"


LevelManager::LevelManager(b2World* world)
{
	theWorld = world;
	Platform platform = Platform(theWorld, 0, 500, 1000, 100, "Platform");
}


LevelManager::~LevelManager()
{
}
