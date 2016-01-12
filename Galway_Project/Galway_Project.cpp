// Galway_Project.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <atomic>
using std::atomic_int;

Player* player1, *player2;

atomic_int numActiveReaders = 0;//the number of active readers

Semaphore* readWriteSem = new Semaphore();//semaphore lock for access to the data

SDL_mutex* readMutex = SDL_CreateMutex();//lock for reader access to numActiveReaders

atomic_int dataToManipulate = 0;

//fps counter: http://lazyfoo.net/tutorials/SDL/24_calculating_frame_rate/index.php

int updateKeyboardStateOnThread(void* threadData)
{
	while (updateKeyboardStateOnThread)
	{
		if (readWriteSem->GetCurrentValue() == 1)
		{
			//std::cout << "my thread moving into critical section" << std::endl;
			readWriteSem->P();
			//std::cout << "Writing data." << std::endl;
			InputManager::GetInstance()->UpdateKeyboardState();
			readWriteSem->V();
			//std::cout << "my thread exiting critical section" << std::endl;
		}
		//else std::cout << "Writer waiting" << std::endl;
	}
	return 0;
}

void ReaderProcess()
{
	if (readWriteSem->GetCurrentValue() == 1)
	{
		SDL_LockMutex(readMutex);
		numActiveReaders += 1;

		if (numActiveReaders == 1)
			readWriteSem->P();

		SDL_UnlockMutex(readMutex);

		//read data
		//std::cout << "Reading data." << std::endl;
		player1->MovePlayer();
		player2->MovePlayer();

		SDL_LockMutex(readMutex);

		numActiveReaders -= 1;

		if (numActiveReaders == 0)
			readWriteSem->V();

		SDL_UnlockMutex(readMutex);
	}
	//else std::cout << "Reader waiting" << std::endl;
}

void CreateGround(b2World& World, float X, float Y)
{
	b2BodyDef BodyDef;
	BodyDef.position = b2Vec2(X / 30.f, Y / 30.f);
	BodyDef.type = b2_staticBody;
	b2Body* Body = World.CreateBody(&BodyDef);

	b2PolygonShape Shape;
	Shape.SetAsBox((10000 / 2) / 30, (16.f / 2) / 30); // Creates a box shape. Divide your desired width and height by 2.
	b2FixtureDef FixtureDef;
	FixtureDef.density = 0.f;  // Sets the density of the body
	FixtureDef.shape = &Shape; // Sets the shape
	FixtureDef.userData = "Ground";
	Body->CreateFixture(&FixtureDef); // Apply the fixture definition
}

int main(int argc, char *argv[])
{
	Uint32 startTicks = SDL_GetTicks();
	int countedFrames = 0;

	b2Vec2 Gravity(0.f, 9.8f);
	b2World world(Gravity);

	LevelManager::GetInstance()->SetUpLevels(&world);

	ContactListener contact = ContactListener(LevelManager::GetInstance());
	world.SetContactListener(&contact);

	player1 = new Player(&world, 100, 100, true);
	player2 = new Player(&world, 300, 100, false);

	Uint32 lastFrameTime = 0;
	Uint32 frameDelay = 0;

	SDL_Event e;
	bool quit = false;

	AudioManager::GetInstance()->Init();
	AudioManager::GetInstance()->LoadMedia();

	int d = 0;

	SDL_Thread* updateKeyboardThread = SDL_CreateThread(updateKeyboardStateOnThread, "Thread updating keyboard state", (void*)d);
	bool updateKeyboardStateOnThread = true;
	//SDL_Thread* updatePolledEventsThread = SDL_CreateThread(updatePolledEventsOnThread, "update polled event thread", static_cast<void*>(&e));

	while (!quit)
	{
		// Update loop
		// gets the deltaTime between frames, pass 'frameDelay' to updates
		Uint32 currentFrameTime = SDL_GetTicks();
		if (currentFrameTime > lastFrameTime)
		{
			frameDelay = currentFrameTime - lastFrameTime;
			lastFrameTime = currentFrameTime;
		}
		
		Render::GetInstance()->Update();
		
		//move the simulation forward
		float32 timeStep = 1.0f / 60.0f;
		int32 velocityIterations = 6;
		int32 positionIterations = 2;
		world.Step(timeStep, velocityIterations, positionIterations);

		LevelManager::GetInstance()->Update();

		player1->Update(&world);
		player2->Update(&world);

		ReaderProcess();

		Uint32 time = 0;
		time = SDL_GetTicks() - startTicks;

		//Calculate and correct fps 
		float avgFPS = countedFrames / (time / 1000.f ); 
		if( avgFPS > 2000000 ) 
		{ 
			avgFPS = 0; 
		}

		//output the average fps
		std::cout << "Average FPS: " << avgFPS << std::endl;

		

		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			InputManager::GetInstance()->UpdatePolledEvents(e);

			//User requests quit
			if (e.type == SDL_QUIT) //user presses close button on window
			{
				quit = true;
			}

			//User presses a key
			else if (e.type == SDL_KEYDOWN)
			{
				switch (e.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					quit = true;
					updateKeyboardStateOnThread = false;
					break;
				default:
					break;
				}


			}
		}//End Poll Events
		//InputManager::GetInstance()->UpdateKeyboardState();

		++countedFrames;
	}//End Game loop

	SDL_WaitThread(updateKeyboardThread, NULL);

	SDL_Quit();
    return 0;
} //End Main

