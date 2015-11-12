#pragma once
#ifndef Platform_H
#define Platform_H
#include <iostream>
#include <SDL.h>
//#include "res_path.h"
#include <SDL_ttf.h>  


class Platform {
private:
	//sprite rendering variables 
	SDL_Surface *sprite;
	SDL_Rect* rcSprite;
	float yPos;
	//box2d variables
	b2World* mWorld;
	b2Body* mBody;
	b2BodyDef mBodyDef;
	b2PolygonShape mShape;
	b2FixtureDef mFixtureDef;
	void createBox2dBody(float, float, float, float, std::string name);
	void LoadAssets(float, float, float, float); 
	b2Vec2 mSize;
	bool moving;
	int moveDistance = 0;
	int offset = 0;

public:
	Platform(b2World*, float, float, float, float, std::string name);
	void ToggleMove();
	void Update();
	b2Vec2 getSize(); 
	void ChangeLevel();
};

#endif