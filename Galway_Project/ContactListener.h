#pragma once
#ifndef CONTACTLISTENER_H
#define CONTACTLISTENER_H

#include "Build\Box2D.h" 

#include "Player.h" 
#include "Platform.h" 

class ContactListener : public b2ContactListener {
private:
	//Level* level;
	//Menu* menu;
public:

	ContactListener() : b2ContactListener() {
		
	}

	void PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
	{
		void* fixAType = contact->GetFixtureA()->GetBody()->GetUserData();
		void* fixBType = contact->GetFixtureB()->GetBody()->GetUserData();

		if (fixAType == "Player" && fixBType == "Bullet"
			|| fixAType == "Bullet" && fixBType == "Player")
		{
			if (fixAType == "Player")
			{
				void* bodyUserData1 = contact->GetFixtureA()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureB()->GetUserData();

				if (static_cast<Player*>(bodyUserData1)->isPlayer1() && static_cast<Bullet*>(bodyUserData2)->isBullet1()
					|| static_cast<Player*>(bodyUserData1)->isPlayer1() == false && static_cast<Bullet*>(bodyUserData2)->isBullet1() == false)
				{
					contact->SetEnabled(false);
				}
				else
				{

				}
			}
			if (fixAType == "Bullet")
			{
				void* bodyUserData1 = contact->GetFixtureB()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureA()->GetUserData();

				if (static_cast<Player*>(bodyUserData1)->isPlayer1() && static_cast<Bullet*>(bodyUserData2)->isBullet1()
					|| static_cast<Player*>(bodyUserData1)->isPlayer1() == false && static_cast<Bullet*>(bodyUserData2)->isBullet1() == false)
				{
					contact->SetEnabled(false);
				}
				else
				{

				}
			}
		}
	}

	void BeginContact(b2Contact* contact)
	{
		void* fixAType = contact->GetFixtureA()->GetBody()->GetUserData();
		void* fixBType = contact->GetFixtureB()->GetBody()->GetUserData();

		if (fixAType == "Player" && fixBType == "Platform"
			|| fixAType == "Platform" && fixBType == "Player") {
			if (fixAType == "Player") {
				void* bodyUserData1 = contact->GetFixtureA()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureB()->GetUserData();
				b2Vec2 posPlat = contact->GetFixtureB()->GetBody()->GetPosition();

				b2Vec2 posPlayer = contact->GetFixtureA()->GetBody()->GetPosition();

				if (posPlat.y - (20 / 60.0f) > posPlayer.y + 16 / 30.0f)
					static_cast<Player*>(bodyUserData1)->Ground();
				static_cast<Platform*>(bodyUserData2)->ToggleMove();
			}
			else if (fixBType == "Player") {
				void* bodyUserData1 = contact->GetFixtureB()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureA()->GetUserData();
				b2Vec2 posPlat = contact->GetFixtureA()->GetBody()->GetPosition();

				b2Vec2 posPlayer = contact->GetFixtureB()->GetBody()->GetPosition();

				if (posPlat.y - (20 / 60.0f) > posPlayer.y + 16 / 30.0f)
					static_cast<Player*>(bodyUserData1)->Ground();

				static_cast<Platform*>(bodyUserData2)->ToggleMove();
			}
		}
	}

	void EndContact(b2Contact* contact) {
		void* fixAType = contact->GetFixtureA()->GetBody()->GetUserData();
		void* fixBType = contact->GetFixtureB()->GetBody()->GetUserData();
	}
};
#endif