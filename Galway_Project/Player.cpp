#include "stdafx.h"
#include "Player.h"

Player::Player(b2World* world, float x, float y,bool isPlayer1) : m_world(world) {
	reset = false;
	grounded = true;
	resetPos = b2Vec2(10, 350);
	createBox2dBody(x, y,isPlayer1);
	LoadAssets(x, y);
}

void Player::createBox2dBody(float x, float y,bool isPlayer1) {
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(x / 30, y / 30);
	if (isPlayer1) { bodyDef.userData = "Player1"; }
	else { bodyDef.userData = "Player2"; }
	bodyDef.gravityScale = 1;
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

void Player::LoadAssets(float x, float y) {
	std::string basepath(SDL_GetBasePath());
	std::string imagePath = basepath + "player.bmp";
	sprite = SDL_LoadBMP(imagePath.c_str());
	spriteRect = Render::GetInstance()->AddSurfaceToRenderer(sprite, x, y);
}

void Player::MovePlayer() {

	vel = body->GetLinearVelocity();
	desiredVelX = 0;
	desiredVelY = 0;

	//moving left and right
	if (body->GetUserData() == "Player1")
	{
		if (InputManager::GetInstance()->IsKeyHeld(SDLK_a)) //tuples have weird syntax, get<index>(tuple) is the same as array[index]
		{
			body->SetTransform(b2Vec2(body->GetPosition().x - 0.3, body->GetPosition().y), 0);
		}

		if (InputManager::GetInstance()->IsKeyHeld(SDLK_d))
		{
			body->SetTransform(b2Vec2(body->GetPosition().x + 0.3, body->GetPosition().y), 0);
		}

		if (InputManager::GetInstance()->IsKeyDown(SDLK_w))
		{
			if (grounded)
			{
				desiredVelY = -100;
				grounded = false;
			}
		}
	}
	else if (body->GetUserData() == "Player2")
	{
		if (InputManager::GetInstance()->IsKeyHeld(SDLK_LEFT)) //tuples have weird syntax, get<index>(tuple) is the same as array[index]
		{
			body->SetTransform(b2Vec2(body->GetPosition().x - 0.3, body->GetPosition().y), 0);
		}

		if (InputManager::GetInstance()->IsKeyHeld(SDLK_RIGHT))
		{
			body->SetTransform(b2Vec2(body->GetPosition().x + 0.3, body->GetPosition().y), 0);
		}

		if (InputManager::GetInstance()->IsKeyDown(SDLK_UP))
		{
			if (grounded)
			{
				desiredVelY = -100;
				grounded = false;
			}
		}
	}

	velChangeX = desiredVelX - vel.x;

	impulseX = body->GetMass() * desiredVelX;
	impulseY = body->GetMass() * desiredVelY;

	body->ApplyLinearImpulse(b2Vec2(impulseX, impulseY), body->GetWorldCenter(), true);
}

void Player::Update(b2World* world) {
	if (reset) {
		body->SetTransform(resetPos, 0);
		reset = false;
	}

	spriteRect->x = body->GetPosition().x * 30;
	spriteRect->y = body->GetPosition().y * 30;
}

void Player::Reset() {
	reset = true;
}

void Player::Ground()
{
	grounded = true;
}