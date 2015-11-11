#include "stdafx.h"
#include "Player.h"

//constructor
Player::Player()
{

}

//destructor
Player::~Player()
{

}

//update the player
void Player::Update()
{

}

//move the player horizontally
void Player::Move()
{

}

//move the player vertically upwards
void Player::Jump()
{
	if (canJump == true)//so if the player is able to jump(i.e. not already in the air)
	{
		float impulse = -180;
		body->ApplyLinearImpulse(b2Vec2(0, impulse), body->GetWorldCenter(), true);
		canJump = false;
	}
}

//Reset the player to their starting position
void Player::Reset()
{

}