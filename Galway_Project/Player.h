#pragma once
#ifndef Player_H
#define Player_H

#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <Build\Box2D.h>
#include "Render.h" 
#include <tuple>

using std::tuple;
using std::make_tuple;
using std::get;

class Player {
public:
	Player() {};
	Player(b2World*, float, float,bool);
	void createBox2dBody(float, float,bool);
	void LoadAssets(float, float);
	void MovePlayer();
	void Update(b2World* world);
	void Shoot();
	void Reset();
	void Ground();

	bool isPlayer1();
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
	float speed;
	bool player1; 
	Bullet* bullet;
	int direction;

	tuple<bool, bool, bool> playerKeys;
	enum playerActions { LEFT, RIGHT, UP };
	float desiredVelX;
	float desiredVelY = 0;
	float velChangeX;
	float velChangeY;
	float impulseX;
	float impulseY;

	bool grounded;

};
#endif