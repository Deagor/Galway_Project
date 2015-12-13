#pragma once
class LevelManager
{
private:
	LevelManager()
	{

	}
	std::vector<Platform*> platforms;
	std::vector<Platform*> boundries;

	Player* player1,* player2;

	b2World* theWorld;

	static bool instanceFlag;
	static LevelManager *instance;

public:
	static LevelManager* GetInstance();
	~LevelManager()
	{
		instanceFlag = false;
	}

	//LevelManager(b2World*);

	void SetUpLevels(b2World*);

	void Update();
	void ChangeLevel();
	int MovePlayer1(void* data);
	int MovePlayer2(void* data);
};

