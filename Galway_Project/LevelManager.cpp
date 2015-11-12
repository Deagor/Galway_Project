#include "stdafx.h"
#include "LevelManager.h"


LevelManager::LevelManager(b2World* world)
{
	theWorld = world;

	Platform* platform = new Platform(theWorld, 40, 580, 150, 20, "Platform");
	Platform* platform2 = new Platform(theWorld, 1090, 580, 150, 20, "Platform");
	Platform* platform3 = new Platform(theWorld, 300, 500, 200, 20, "Platform");
	Platform* platform4 = new Platform(theWorld, 750, 500, 200, 20, "Platform");


	Platform* platform5 = new Platform(theWorld, 300, 300, 200, 20, "Platform");
	Platform* platform6 = new Platform(theWorld, 750, 300, 200, 20, "Platform");

	Platform* platform7 = new Platform(theWorld, 150, 400, 150, 20, "Platform");
	Platform* platform8 = new Platform(theWorld, 950, 400, 150, 20, "Platform");

	Platform* platform9 = new Platform(theWorld, 40, 190, 150, 20, "Platform");
	Platform* platform9nd3Q = new Platform(theWorld, 520, 190, 150, 20, "Platform");
	Platform* platform10 = new Platform(theWorld, 1090, 190, 150, 20, "Platform");
	Platform* platform11 = new Platform(theWorld, 560, 400, 100, 20,"Platform");
	

	Platform* boundryGround = new Platform(theWorld, 0, 680, 1280, 40, "Platform");
	Platform* boundry1 = new Platform(theWorld, 0, 0, 1280, 40, "Boundary");
	Platform* boundry2 = new Platform(theWorld, 0, 0, 40, 720, "Boundary");
	Platform* boundry3 = new Platform(theWorld, 1240, 0, 40, 720, "Boundary");

	boundries.push_back(boundry1);
	boundries.push_back(boundry2);
	boundries.push_back(boundry3);
	platforms.push_back(boundryGround);

	player1 = new Player(theWorld, 100, 100, true);
	player2 = new Player(theWorld, 300, 100, false);
}

void LevelManager::Update()
{
	player1->Update(theWorld);
	player1->MovePlayer();

	player2->Update(theWorld);
	player2->MovePlayer();
}


LevelManager::~LevelManager()
{
}
