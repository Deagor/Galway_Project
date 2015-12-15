#pragma once
#ifndef ENEMY_H
#define ENEMY_H

enum Directions
{
	LEFT,
	RIGHT,
	NOTMOVING
};

class Enemy
{
private:
	bool reset;
	b2Vec2 resetPos;
	//move this to move your sprite (To bodydef position)
	SDL_Rect* spriteRect;
	SDL_Surface *sprite;
	b2BodyDef bodyDef;
	b2PolygonShape dynamicBox;
	b2World* m_world;
	b2Body* body;
	b2FixtureDef fixtureDef;
	b2Vec2 vel;
	bool grounded;

	float desiredVelX;
	float desiredVelY = 0;
	float velChangeX;
	float velChangeY;
	float impulseX;
	float impulseY;
	float speed;

	bool alive = true;

	Directions direction;
	b2Vec2 playerLocation; 

	Player* player1;
	Player* player2;

	SDL_Thread* targettingThread;

public:
	Enemy(b2World*, float, float);

	//destructor(destroy the body!)
	~Enemy();

	//create the box2dBody
	void createBox2dBody(float, float);

	//load the texture
	void LoadAssets(float, float);

	//update the sprite rectangle position
	void Update();

	void Movement();

	void SetPlayerTarget();

	void Ground(bool);

	void CreateThread(Player*, Player*);

	void Destroy();

	float Distance(b2Vec2, b2Vec2);

	bool Alive();
};

#endif