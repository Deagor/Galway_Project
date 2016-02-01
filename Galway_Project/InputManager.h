#ifndef INPUTMANAGER 
#define INPUTMANAGER

class InputManager
{
public:
    //Functions
    static InputManager* GetInstance();
    ~InputManager()
    {
        instanceFlag = false;
    }

    void UpdateKeyboardState();
    void UpdatePolledEvents(SDL_Event e);
    bool IsKeyDown(SDL_Keycode key);
    bool IsKeyHeld(SDL_Keycode key);
    bool IsKeyUp(SDL_Keycode key);

    bool getShouldQuit();

    //Variables

private:
    //Functions
    InputManager()
    {
        HeldKeyMutex = SDL_CreateMutex();
        DownKeyMutex = SDL_CreateMutex();
        quitMutex = SDL_CreateMutex();
        isKeyUpMutex = SDL_CreateMutex();
        //private constructor
        downKeys = std::vector<SDL_Keycode>();
        heldKeys = std::vector<SDL_Keycode>();
        upKeys = std::vector<SDL_Keycode>();
        shouldQuit = false;
    }

    SDL_mutex* HeldKeyMutex;
    SDL_mutex* DownKeyMutex;

    SDL_mutex* isKeyUpMutex;
    SDL_mutex* quitMutex;
    //Variables
    std::vector<SDL_Keycode> downKeys;
    std::vector<SDL_Keycode> heldKeys;
    std::vector<SDL_Keycode> upKeys;
    std::vector<SDL_Keycode> mouseClicks;

    bool shouldQuit;
    static bool instanceFlag;
    static InputManager *instance;
};

#endif