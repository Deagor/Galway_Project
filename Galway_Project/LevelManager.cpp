#include "stdafx.h"
#include "Enemy.h"
#include "LevelManager.h"

LevelManager::LevelManager(b2World* world)
{ 
	theWorld = world;

	//**Level 1**
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
	Platform* platform11 = new Platform(theWorld, 560, 400, 100, 20, "Platform");


	//**Level 2**
	Platform* platform12 = new Platform(theWorld, 40, 580 - 720, 150, 20, "Platform");
	Platform* platform13 = new Platform(theWorld, 1090, 580 - 720, 150, 20, "Platform");
	Platform* platform14 = new Platform(theWorld, 300, 500 - 720, 200, 20, "Platform");
	Platform* platform15 = new Platform(theWorld, 750, 500 - 720, 200, 20, "Platform");


	Platform* platform16 = new Platform(theWorld, 520, 400 - 720, 200, 20, "Platform");

	Platform* platform17 = new Platform(theWorld, 40, 200 - 720, 150, 20, "Platform");
	Platform* platform18 = new Platform(theWorld, 1090, 200 - 720, 150, 20, "Platform");
	Platform* platform19 = new Platform(theWorld, 300, 300 - 720, 200, 20, "Platform");
	Platform* platform20 = new Platform(theWorld, 750, 300 - 720, 200, 20, "Platform");
	Platform* platform21 = new Platform(theWorld, 515, 140 - 720, 245, 20, "Platform");

	//**Level 3**
	Platform* platform22 = new Platform(theWorld, 520, 580 - 1440, 80, 20, "Platform");
	Platform* platform23 = new Platform(theWorld, 300, 500 - 1440, 150, 20, "Platform");
	Platform* platform24 = new Platform(theWorld, 700, 500 - 1440, 150, 20, "Platform");
	Platform* platform25 = new Platform(theWorld, 150, 400 - 1440, 100, 20, "Platform");
	Platform* platform26 = new Platform(theWorld, 850, 400 - 1440, 250, 20, "Platform");

	Platform* platform27 = new Platform(theWorld, 300, 120 - 1440, 600, 20, "Platform");
	Platform* platform28 = new Platform(theWorld, 520, 340 - 1440, 150, 20, "Platform");
	Platform* platform29 = new Platform(theWorld, 750, 240 - 1440, 80, 20, "Platform");
	Platform* platform30 = new Platform(theWorld, 950, 180 - 1440, 150, 20, "Platform");

	Platform* platform31 = new Platform(theWorld, 240, 240 - 1440, 245, 20, "Platform");
	Platform* platform32 = new Platform(theWorld, 100, 180 - 1440, 100, 20, "Platform");

	platforms.push_back(platform);
	platforms.push_back(platform2);
	platforms.push_back(platform3);
	platforms.push_back(platform4);
	platforms.push_back(platform5);
	platforms.push_back(platform6);
	platforms.push_back(platform7);
	platforms.push_back(platform8);
	platforms.push_back(platform9);
	platforms.push_back(platform9nd3Q);
	platforms.push_back(platform10);
	platforms.push_back(platform11);
	platforms.push_back(platform12);
	platforms.push_back(platform13);
	platforms.push_back(platform14);
	platforms.push_back(platform15);
	platforms.push_back(platform16);
	platforms.push_back(platform17);
	platforms.push_back(platform18);
	platforms.push_back(platform19);
	platforms.push_back(platform20);
	platforms.push_back(platform21);
	platforms.push_back(platform22);
	platforms.push_back(platform23);
	platforms.push_back(platform24);
	platforms.push_back(platform25);
	platforms.push_back(platform26);
	platforms.push_back(platform27);
	platforms.push_back(platform28);
	platforms.push_back(platform29);
	platforms.push_back(platform30);
	platforms.push_back(platform31);
	platforms.push_back(platform32);

	Platform* boundryGround = new Platform(theWorld, 0, 680, 1280, 40, "Ground");
	Platform* boundry1 = new Platform(theWorld, 0, 0, 1280, 40, "Boundary");
	Platform* boundry2 = new Platform(theWorld, 0, 0, 40, 720, "Boundary");
	Platform* boundry3 = new Platform(theWorld, 1240, 0, 40, 720, "Boundary");

	boundries.push_back(boundry1);
	boundries.push_back(boundry2);
	boundries.push_back(boundry3);
	boundries.push_back(boundryGround);

	player1 = new Player(theWorld, 100, 100, true);
	player2 = new Player(theWorld, 300, 100, false);
	players = std::pair<Player*, Player*>(player1, player2);

	eManager = new EnemyManager(world, 500, 100, &enemies, player1, player2);  
}

void LevelManager::Update()
{
	player1->Update(theWorld);
	player1->MovePlayer();

	player2->Update(theWorld);
	player2->MovePlayer();

	int size = enemies.size();

	for (int i = 0; i < size; i++) {
		enemies[i]->Update();
	}

	size = platforms.size();

	for (int i = 0; i < size; i++) {
		platforms[i]->Update();
	}

	if (timer > 45) {
		eManager->CreateEnemy();
		timer = 0;
	}
	timer++;
}

void LevelManager::ChangeLevel() {
	int size = platforms.size();

	for (int i = 0; i < size; i++) {
		platforms[i]->ChangeLevel();
	}

	player1->PickupBullet();
	player2->PickupBullet();
}

LevelManager::~LevelManager()
{
}
