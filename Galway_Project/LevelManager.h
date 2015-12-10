#pragma once
class LevelManager
{
private:
	std::vector<Platform*> platforms;
	std::vector<Platform*> boundries;

	Player* player1,* player2;

	b2World* theWorld;

public:
	LevelManager(b2World*);
	void Update();
	~LevelManager();
	void ChangeLevel();
	int MovePlayer1(void* data);
	int MovePlayer2(void* data);
};

