#pragma once
#ifndef BODYDESTROYER
#define BODYDESTROYER 

class BodyDestroyer {
private:
	BodyDestroyer(b2World*); 
	b2World* world;
	std::vector<b2Body*> bodies;

public:
	static BodyDestroyer* GetInstance(b2World*);
	static BodyDestroyer* GetInstance();

	void AddBody(b2Body*);
	void DestroyBodies();
};
#endif