#include "stdafx.h"
#include "Bullet.h"

Bullet::Bullet(b2World* world, float x, float y, bool player, int curDir) : m_world(world), bulletForPlayer1(player), currentDirection(curDir)
{
	createBox2dBody(x, y);
	LoadAssets(x, y);
}

//destructor(destroy the body!)
Bullet::~Bullet()
{
	m_world->DestroyBody(body);
}

//create the box2dBody
void Bullet::createBox2dBody(float x, float y)
{
	bodyDef.type = b2_kinematicBody;
	bodyDef.position.Set(x / 30, y / 30);
	if(bulletForPlayer1 == true)
		bodyDef.userData = "Bullet1";
	else bodyDef.userData = "Bullet2";
	body = m_world->CreateBody(&bodyDef);
	dynamicBox.SetAsBox((32 / 2.0f) / 30, (36 / 2.0f) / 30);
	fixtureDef.shape = &dynamicBox;

	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	fixtureDef.userData = this;
	fixtureDef.restitution = b2MixRestitution(0, 0);

	body->CreateFixture(&fixtureDef);
	body->SetFixedRotation(true);
}

//load the texture
void Bullet::LoadAssets(float x, float y)
{
	std::string basepath(SDL_GetBasePath());
	std::string imagePath = basepath + "bullet.bmp";
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
	spriteRect->x = body->GetPosition().x * 30;
	spriteRect->y = body->GetPosition().y * 30;
}

//if the bullet hits a wall then set velocity to 0 and change body type so it is affected by gravity
void Bullet::HitWall()
{
	body->SetLinearVelocity(b2Vec2(0, 0));
	bodyDef.type = b2_dynamicBody;
}