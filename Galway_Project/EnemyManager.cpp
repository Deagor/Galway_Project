#include "stdafx.h"
#include "EnemyManager.h"

EnemyManager::EnemyManager(b2World * world, float x, float y, std::vector<Enemy*>* e, Player* player1, Player* player2) :
	mWorld(world), spawnPosition(b2Vec2(x, y)), enemies(e)
{
	p1 = player1;
	p2 = player2;
}

EnemyManager::~EnemyManager()
{
} 

void EnemyManager::CreateEnemy()
{ 
	Enemy* temp = new Enemy(mWorld, spawnPosition.x, spawnPosition.y);
	temp->CreateThread(p1, p2);
	enemies->push_back(temp);
}