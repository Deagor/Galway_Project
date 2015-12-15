#include "stdafx.h"

enum _entityCategory {
	BOUNDARY = 0x0001,
	PLATFORM = 0x0002,
	BULLET = 0x0004,
	PLAYER = 0x0008,
	ENEMY = 0x00012
};


Enemy::Enemy(b2World * world, float x, float y) : m_world(world)
{
	grounded = false;
	createBox2dBody(x, y);
	LoadAssets(x, y);
	direction = Directions::LEFT;
	speed = 0.15f;
}

Enemy::~Enemy()
{
}

void Enemy::createBox2dBody(float x, float y)
{
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(x / 30, y / 30);
	bodyDef.userData = "Enemy";
	body = m_world->CreateBody(&bodyDef);
	dynamicBox.SetAsBox((16 / 2.0f) / 30, (16 / 2.0f) / 30);
	fixtureDef.shape = &dynamicBox;

	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	fixtureDef.userData = this;
	fixtureDef.restitution = b2MixRestitution(0, 0);

	fixtureDef.filter.categoryBits = ENEMY;
	fixtureDef.filter.maskBits = PLAYER | PLATFORM | ENEMY;

	body->CreateFixture(&fixtureDef);
	body->SetFixedRotation(true);
	body->SetGravityScale(1);
}

void Enemy::LoadAssets(float x, float y)
{
	std::string basepath(SDL_GetBasePath());
	std::string imagePath;
	imagePath = basepath + "../Sprites/enemy.bmp";
	sprite = SDL_LoadBMP(imagePath.c_str());
	spriteRect = Render::GetInstance()->AddSurfaceToRenderer(sprite, x, y);
}

void Enemy::Update()
{
	if (alive) {
		spriteRect->x = body->GetPosition().x * 30 - 8;
		spriteRect->y = body->GetPosition().y * 30 - 8;

		Movement();
	}
}

void Enemy::Movement()
{
	switch (direction) {
	case (Directions::NOTMOVING) :
		//Do NOTHING
		break;
	case (Directions::LEFT) :
		if (grounded) {
			if (body->GetLinearVelocity().x < 5)
				body->ApplyForce(b2Vec2(10, body->GetPosition().y), body->GetLocalCenter(), true);
		}
							break;
	case (Directions::RIGHT) :
		if (grounded) {
			if (body->GetLinearVelocity().x > -5)
				body->ApplyForce(b2Vec2(-10, body->GetPosition().y), body->GetLocalCenter(), true);
		}
							 break;
	}
}

void Enemy::SetPlayerTarget(b2Vec2 p1, b2Vec2 p2)
{
	std::cout << "Method Called" << std::endl;
}

void Enemy::Ground(bool ground)
{
	grounded = ground;
}

void Enemy::Destroy() { 
	BodyDestroyer::GetInstance()->AddBody(body);
	spriteRect->x = -10000000;
	alive = false;
}
