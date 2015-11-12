#pragma once
class LevelManager
{
private:
	std::vector<Platform*> platforms;
	b2World* theWorld;
public:
	LevelManager(b2World*);
	~LevelManager();
};

