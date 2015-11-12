#include "stdafx.h"
#include "Bullet.h"

Bullet::Bullet(b2World* world, float x, float y, bool player) : m_world(world), bulletForPlayer1(player)
{
	reset = false;
	createBox2dBody(x, y);
	resetPos = b2Vec2(-500, 0);
	LoadAssets(x, y);
	currentDirection = NOTMOVING;

	bullet1 = player;
}

//destructor(destroy the body!)
Bullet::~Bullet()
{
	m_world->DestroyBody(body);
}

//create the box2dBody
void Bullet::createBox2dBody(float x, float y)
{
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(x / 30, y / 30);
	if(bulletForPlayer1 == true)
		bodyDef.userData = "Bullet";
	else bodyDef.userData = "Bullet";
	body = m_world->CreateBody(&bodyDef);
	dynamicBox.SetAsBox((7 / 2.0f) / 30, (7 / 2.0f) / 30);
	fixtureDef.shape = &dynamicBox;

	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	fixtureDef.userData = this;
	fixtureDef.restitution = b2MixRestitution(0, 0);

	body->CreateFixture(&fixtureDef);
	body->SetFixedRotation(true);
	body->SetGravityScale(0);
}

//load the texture
void Bullet::LoadAssets(float x, float y)
{
	std::string basepath(SDL_GetBasePath());
	std::string imagePath;
	if (bulletForPlayer1 == true)
		imagePath = basepath + "../Sprites/player1Bullet.bmp";
	else imagePath = basepath + "../Sprites/player2Bullet.bmp";
	sprite = SDL_LoadBMP(imagePath.c_str());
	spriteRect = Render::GetInstance()->AddSurfaceToRenderer(sprite, x, y);
}

//move the bullet in its current direction
void Bullet::Move()
{
	vel = body->GetLinearVelocity();
	desiredVelX = 0;
	desiredVelY = 0;

	if(currentDirection == LEFT)
	{
		body->SetTransform(b2Vec2(body->GetPosition().x - 0.3, body->GetPosition().y), 0);
	}
	else if (currentDirection == RIGHT)
	{
		body->SetTransform(b2Vec2(body->GetPosition().x + 0.3, body->GetPosition().y), 0);
	}
	else if (currentDirection == NOTMOVING)
	{
		body->SetTransform(b2Vec2(body->GetPosition().x, body->GetPosition().y), 0);
	}

	velChangeX = desiredVelX - vel.x;

	impulseX = body->GetMass() * desiredVelX;
	impulseY = body->GetMass() * desiredVelY;

	body->ApplyLinearImpulse(b2Vec2(impulseX, impulseY), body->GetWorldCenter(), true);
}

//update the sprite rectangle position
void Bullet::Update()
{
	if (reset) {
		body->SetTransform(resetPos, 0);
		reset = false;
		bodyDef.type = b2_kinematicBody;
		currentDirection = NOTMOVING;
		body->SetLinearVelocity(b2Vec2(0, 0));
	}

	spriteRect->x = body->GetPosition().x * 30 - 3.5;
	spriteRect->y = body->GetPosition().y * 30 - 3.5;
}

//if the bullet hits a wall then set velocity to 0 and change body type so it is affected by gravity
void Bullet::HitWall()
{
	body->SetLinearVelocity(b2Vec2(0, 0)); 
	body->SetGravityScale(1);
	currentDirection = NOTMOVING;
}

void Bullet::Reset()
{
	reset = true;
}

bool Bullet::isBullet1()
{
	return bullet1;
}

//set the bodies position to be the players position
void Bullet::setPosition(float x, float y)
{
	body->SetTransform(b2Vec2(x,y), 0);
}

void Bullet::setDirection(int direction) {
	currentDirection = direction;
}