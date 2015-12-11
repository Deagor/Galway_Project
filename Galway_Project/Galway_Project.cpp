// Galway_Project.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

//fps counter: http://lazyfoo.net/tutorials/SDL/24_calculating_frame_rate/index.php

int ThreadFunction(void* threadData)
{
	//for (int i = 0; i < 10000; i++)
	//{
	//	std::cout << "Thread Number: " << (int)threadData << std::endl;
	//}
	return 0;
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

	LevelManager lvlMngr(&world);

	ContactListener contact = ContactListener(&lvlMngr);
	world.SetContactListener(&contact);

	Uint32 lastFrameTime = 0;
	Uint32 frameDelay = 0;

	SDL_Event e;
	bool quit = false;

	AudioManager::GetInstance()->Init();
	AudioManager::GetInstance()->LoadMedia();

	int d = 0;
	//SDL_Thread* player1Thread = SDL_CreateThread(lvlMngr.MovePlayer1, "Player1MoveThread", (void*)d);
	//SDL_Thread* player2Thread = SDL_CreateThread(lvlMngr.MovePlayer2, "Player2MoveThread", (void*)d);
	SDL_Thread* testThread = SDL_CreateThread(ThreadFunction, "Test Thread", (void*)d);
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
		lvlMngr.Update();
		
		Uint32 time = 0;
		time = SDL_GetTicks() - startTicks;

		//Calculate and correct fps 
		float avgFPS = countedFrames / (time / 1000.f ); 
		if( avgFPS > 2000000 ) 
		{ 
			avgFPS = 0; 
		}

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
					break;
				default:
					break;
				}


			}
		}//End Poll Events

		InputManager::GetInstance()->UpdateKeyboardState();

		++countedFrames;
	}//End Game loop

	SDL_WaitThread(testThread, NULL);

	SDL_Quit();
    return 0;
} //End Main

