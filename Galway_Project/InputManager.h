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

    //Variables

private:
    //Functions
    InputManager()
    {
        addHeldKeyMutex = SDL_CreateMutex();
        addDownKeyMutex = SDL_CreateMutex();
        removeHeldKeyMutex = SDL_CreateMutex();
        removeDownKeyMutex = SDL_CreateMutex();

        isKeyDownMutex = SDL_CreateMutex();
        isKeyHeldMutex = SDL_CreateMutex();
        isKeyUpMutex = SDL_CreateMutex();
        //private constructor
        downKeys = std::vector<SDL_Keycode>();
        heldKeys = std::vector<SDL_Keycode>();
        upKeys = std::vector<SDL_Keycode>();
    }

    SDL_mutex* HeldKeyMutex;
    SDL_mutex* DownKeyMutex;

    SDL_mutex* isKeyUpMutex;

    //Variables
    std::vector<SDL_Keycode> downKeys;
    std::vector<SDL_Keycode> heldKeys;
    std::vector<SDL_Keycode> upKeys;
    std::vector<SDL_Keycode> mouseClicks;

    static bool instanceFlag;
    static InputManager *instance;
};

#endif