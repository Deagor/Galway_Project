#include "Platform.h" 
#include "stdafx.h"

enum _entityCategory {
	BOUNDARY = 0x0001,
	PLATFORM = 0x0002,
	BULLET = 0x0004,
	PLAYER = 0x0008
};

Platform::Platform(b2World* world, float x, float y, float w, float h, std::string name) : mWorld(world), mSize(w, h)
{
	LoadAssets(x, y, w, h);
	createBox2dBody(x, y, w, h, name);
}

void Platform::createBox2dBody(float x, float y, float w, float h, std::string name) {

	mBodyDef.type = b2_staticBody;

	if (name == "Platform")
	{
		mBodyDef.userData = "Platform";
	}
	else if (name == "Ground")
	{
		mBodyDef.userData = "Ground";
	}
	else
	{
		mBodyDef.userData = "Boundary";
	}

	mBodyDef.position.Set((x + w / 2.0f) / 30.0f, (y + h / 2.0f) / 30.0f);
	mBody = mWorld->CreateBody(&mBodyDef);

	mShape.SetAsBox(w / 60.0f, h / 60.0f);
	mFixtureDef.restitution = b2MixRestitution(0, 0);

	mFixtureDef.shape = &mShape;
	
	mFixtureDef.userData = this;

	mFixtureDef.filter.categoryBits = PLATFORM;
	mFixtureDef.filter.maskBits = PLAYER | BULLET;

	mFixtureDef.density = 1;
	mBody->CreateFixture(&mFixtureDef);
}

void Platform::LoadAssets(float x, float y, float w, float h)
{
	std::string basepath(SDL_GetBasePath());
	std::string imagePath = basepath + "../Sprites/platform.bmp";
	sprite = SDL_LoadBMP(imagePath.c_str());
	rcSprite = Render::GetInstance()->AddSurfaceToRenderer(sprite, x, y);
	yPos = y;
	rcSprite->w = w;
	rcSprite->h = h;
}

void Platform::Update()
{
	if (moveDistance > 200)
	{
		moving = false;
		moveDistance = 100;
	}
	if (moving)
	{
		moveDistance++;
		if (moveDistance <= 100)
		{
			mBody->SetTransform(b2Vec2(mBody->GetPosition().x, mBody->GetPosition().y - 1 / 30.0f), 0);
		}
	}
	else
	{
		if (moveDistance > 0)
		{
			moveDistance--;
			mBody->SetTransform(b2Vec2(mBody->GetPosition().x, mBody->GetPosition().y + 1 / 30.0f), 0);
		}
	}
	rcSprite->x = mBody->GetPosition().x * 30 - mSize.x / 2;
	rcSprite->y = mBody->GetPosition().y * 30 - mSize.y / 2;
}

void Platform::ToggleMove()
{
	moving = true;
}

b2Vec2 Platform::GetSize() const
{
	return mSize;
}