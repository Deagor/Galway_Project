// Galway_Project.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

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
	//fps counter code
	//Set text color as black 
	SDL_Color textColor = { 0, 0, 0, 255 }; //The frames per second timer 
	LTimer fpsTimer; //In memory text stream 
	std::stringstream timeText;
	//Start counting frames per second 
	int countedFrames = 0; 
	fpsTimer.start();

	b2Vec2 Gravity(0.f, 9.8f);
	b2World world(Gravity);

	LevelManager lvlMngr(&world);

	ContactListener contact = ContactListener(&lvlMngr);
	world.SetContactListener(&contact);

	Uint32 lastFrameTime = 0;
	Uint32 frameDelay = 0;

	SDL_Event e;
	bool quit = false;

	BodyDestroyer::GetInstance(&world);

	AudioManager::GetInstance()->Init();
	AudioManager::GetInstance()->LoadMedia();

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
		
		//Calculate and correct fps 
		float avgFPS = countedFrames / ( fpsTimer.getTicks() / 1000.f ); 
		if( avgFPS > 2000000 ) { avgFPS = 0; }

		//std::cout << "FPS is: " << avgFPS << std::endl;

		Render::GetInstance()->Update();
		
		//move the simulation forward
		float32 timeStep = 1.0f / 60.0f;
		int32 velocityIterations = 6;
		int32 positionIterations = 2;
		world.Step(timeStep, velocityIterations, positionIterations);
		lvlMngr.Update(); 

		BodyDestroyer::GetInstance()->DestroyBodies(); 

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

		countedFrames++;
	}//End Game loop
	SDL_Quit();
    return 0;
} //End Main

