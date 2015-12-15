#include "stdafx.h"
#include "BodyDestroyer.h"

static bool instanceFlag = false;
static BodyDestroyer* instance = NULL;

BodyDestroyer* BodyDestroyer::GetInstance() {
	if (instanceFlag)
		return instance;
	else
		return NULL;
}

BodyDestroyer* BodyDestroyer::GetInstance(b2World* w) {
	if (!instanceFlag)
	{
		instance = new BodyDestroyer(w);
		instanceFlag = true;
		return instance;
	}
	else
	{
		return instance;
	}
}

BodyDestroyer::BodyDestroyer(b2World* w) {
	world = w;
}

void BodyDestroyer::AddBody(b2Body* body) {
	bodies.push_back(body);
}

void BodyDestroyer::DestroyBodies() {
	int size = bodies.size();

	for (int i = 0; i < size; i++) {
		world->DestroyBody(bodies[i]);
	}

	bodies.clear();
}