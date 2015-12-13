// Galway_Project.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

//fps counter: http://lazyfoo.net/tutorials/SDL/24_calculating_frame_rate/index.php

int MovePlayer1(void* threadData)
{
	//for (int i = 0; i < 10000; i++)
	//{
	//	std::cout << "Thread Number: " << (int)threadData << std::endl;
	//}
	LevelManager::GetInstance()->MovePlayer1(threadData);
	//std::cout << "calling move player 1 on a thread" << std::endl;
	return 0;
}

int MovePlayer2(void* threadData)
{
	LevelManager::GetInstance()->MovePlayer2(threadData);
	//std::cout << "calling move player 2 on a thread" << std::endl;
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

	LevelManager::GetInstance()->SetUpLevels(&world);

	ContactListener contact = ContactListener(LevelManager::GetInstance());
	world.SetContactListener(&contact);

	Uint32 lastFrameTime = 0;
	Uint32 frameDelay = 0;

	SDL_Event e;
	bool quit = false;

	AudioManager::GetInstance()->Init();
	AudioManager::GetInstance()->LoadMedia();

	int d = 0;

	SDL_Thread* player1MoveThread = SDL_CreateThread(MovePlayer1, "Thread moving player 1", (void*)d);
	SDL_Thread* player2MoveThread = SDL_CreateThread(MovePlayer2, "Thread moving player 2", (void*)d);

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
					break;
				default:
					break;
				}


			}
		}//End Poll Events
		//testThread = SDL_CreateThread(MovePlayer1, "Thread moving player 1", (void*)d);
		InputManager::GetInstance()->UpdateKeyboardState();

		++countedFrames;
	}//End Game loop

	SDL_WaitThread(player1MoveThread, NULL);
	SDL_WaitThread(player2MoveThread, NULL);

	SDL_Quit();
    return 0;
} //End Main

