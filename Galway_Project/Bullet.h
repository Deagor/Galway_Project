#ifndef BULLET_H
#define BULLET_H

class Bullet
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

	float desiredVelX;
	float desiredVelY = 0;
	float velChangeX;
	float velChangeY;
	float impulseX;
	float impulseY;

	bool bullet1;

	bool alive;

	enum Directions
	{
		LEFT,
		RIGHT,
		NOTMOVING
	};
	int currentDirection;

	bool bulletForPlayer1;
public:
	Bullet(b2World*, float, float, bool);

	//destructor(destroy the body!)
	~Bullet();

	//create the box2dBody
	void createBox2dBody(float, float);

	//load the texture
	void LoadAssets(float, float);

	//move the bullet in its current direction
	void Move();

	//update the sprite rectangle position
	void Update();

	//if the bullet hits a wall then set velocity to 0 and change body type so it is affected by gravity
	void HitWall();

	void Reset();

	bool isBullet1();
	//0=Left, 1=Right, 2=Not moving
	void setCurrentDirection(int dir) { currentDirection = dir; }

	//set the bodies position to be the players position
	void setPosition(float x, float y);

	//no comment
	void setDirection(int);

	bool getAlive();
};

#endif