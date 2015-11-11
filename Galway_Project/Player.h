#ifndef PLAYER_H
#define PLAYER_H

class Player
{
public:
	//constructor
	Player();

	//destructor
	~Player();

	//update the player
	void Update();

	//move the player horizontally
	void Move();

	//move the player vertically upwards
	void Jump();

	//Reset the player to their starting position
	void Reset();

private:
	b2FixtureDef fixdef;
	b2BodyDef bodyDef;
	b2Body* body;

	float startX;
	float startY;

	bool canJump;

};

#endif
