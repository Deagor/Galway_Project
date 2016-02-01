// Galway_Project.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <thread>
bool usingThreadsForInput = true;
std::vector<SDL_Event> eventArray;
SDL_sem *semaphore;
SDL_mutex* eventArrayMutex;

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

int updateInputThread(void* ptr)
{
    while (usingThreadsForInput)
    {
        InputManager::GetInstance()->UpdateKeyboardState();
    }
    return true;
}

int UpdateEvents(void* ptr)
{
    while (usingThreadsForInput)
    {
        SDL_SemWait(semaphore);

        SDL_LockMutex(eventArrayMutex);
        if (eventArray.size() != 0)
        {
            std::cout << std::this_thread::get_id() << std::endl;
            auto temp = eventArray.back();
            eventArray.pop_back();
            SDL_UnlockMutex(eventArrayMutex);
            
            InputManager::GetInstance()->UpdatePolledEvents(temp);
        }
    }
    return 0;
}

int main(int argc, char *argv[])
{
    b2Vec2 Gravity(0.f, 9.8f);
    b2World world(Gravity);

    eventArray.reserve(10);

    eventArrayMutex = SDL_CreateMutex();
    semaphore = SDL_CreateSemaphore(0);

    

    LevelManager lvlMngr(&world);

    ContactListener contact = ContactListener(&lvlMngr);
    world.SetContactListener(&contact);

    Uint32 lastFrameTime = 0;
    Uint32 frameDelay = 0;

    SDL_Event e;
    bool quit = false;

    AudioManager::GetInstance()->Init();
    AudioManager::GetInstance()->LoadMedia();

    SDL_Thread* InputThread = SDL_CreateThread(updateInputThread, "Checking Input", (void*)NULL);

    SDL_Thread* EventThread1 = SDL_CreateThread(UpdateEvents, "Checking Events", (void*)NULL);
    SDL_Thread* EventThread2 = SDL_CreateThread(UpdateEvents, "Checking Events", (void*)NULL);
    SDL_Thread* EventThread3 = SDL_CreateThread(UpdateEvents, "Checking Events", (void*)NULL);

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

        if (InputManager::GetInstance()->IsKeyDown(SDLK_ESCAPE))
        {
            quit = true;
            usingThreadsForInput = false;
        }


        if (InputManager::GetInstance()->getShouldQuit()) { quit = true; usingThreadsForInput = false; }

        //Handle events on queue
        while (SDL_PollEvent(&e) != 0)
        {
            SDL_LockMutex(eventArrayMutex);
            eventArray.push_back(e);
            SDL_UnlockMutex(eventArrayMutex);
            SDL_SemPost(semaphore);
        }

        //InputManager::GetInstance()->UpdateKeyboardState();
    }//End Game loop
    SDL_WaitThread(InputThread, NULL);
    SDL_Quit();
    return 0;
} //End Main

