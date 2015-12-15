#pragma once
class LevelManager
{
private:
	std::vector<Platform*> platforms;
	std::vector<Platform*> boundries;

	Player* player1,* player2;
	Enemy* enemy;
	b2World* theWorld;
	SDL_Thread* enemyTargetThread;
public:
	LevelManager(b2World*);
	void Update();
	~LevelManager();
	void ChangeLevel(); 
};

