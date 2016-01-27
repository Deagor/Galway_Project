#pragma once
class LevelManager
{
private:
	std::vector<Platform*> platforms;
	std::vector<Platform*> boundries;
	std::vector<Enemy*> enemies; 
	std::pair <Player*, Player*> players;

	Player* player1,* player2;
	EnemyManager* eManager; 
	b2World* theWorld;
	SDL_Thread* enemyTargetThread;

	int timer = 0;
public:
	LevelManager(b2World*);
	void Update();
	~LevelManager();
	void ChangeLevel(); 
};

