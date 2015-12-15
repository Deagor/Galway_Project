#pragma once
#ifndef ENEMYMANAGER_h
#define ENEMYMANAGER_h
 
class EnemyManager
{
private: 
	b2Vec2 spawnPosition;
	b2World* mWorld;
	std::vector<Enemy*>* enemies;
	int timeBetweenSpawn;
	Player* p1;
	Player* p2;
public: 
	EnemyManager(b2World * world, float x, float y, std::vector<Enemy*>* e, Player * player1, Player * player2);

	//destructor(destroy the body!)
	~EnemyManager();

	void CreateEnemy();


	 
};

#endif#pragma once
