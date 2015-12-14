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
		//processMutex = SDL_CreateMutex();
		//heldKeysPushBackMutex = SDL_CreateMutex();
		//addDownKeysMutex = SDL_CreateMutex();
		//heldKeysEraseMutex = SDL_CreateMutex();
		//eraseDownKeysMutex = SDL_CreateMutex();

		//isKeyDownMutex = SDL_CreateMutex();
		//isKeyHeldMutex = SDL_CreateMutex();
		//isKeyUpMutex = SDL_CreateMutex();
	}

	void UpdateKeyboardState();
	void UpdatePolledEvents(SDL_Event e);

	void downKeysPushBack(SDL_Keycode k);
	void downKeysErase();
	void heldKeysPushBack(SDL_Keycode k);
	void heldKeysErase(SDL_Keycode k);

	bool IsKeyDown(SDL_Keycode key);
	bool IsKeyHeld(SDL_Keycode key);
	bool IsKeyUp(SDL_Keycode key);

	//Variables

private:
	//Functions
	InputManager()
	{
		//private constructor
		downKeys = std::vector<SDL_Keycode>();
		heldKeys = std::vector<SDL_Keycode>();
		upKeys = std::vector<SDL_Keycode>();
	}

	//Variables
	std::vector<SDL_Keycode> downKeys;
	std::vector<SDL_Keycode> heldKeys;
	std::vector<SDL_Keycode> upKeys;
	std::vector<SDL_Keycode> mouseClicks;

	//SDL_mutex* processMutex = NULL;

	//SDL_mutex* heldKeysPushBackMutex = NULL;
	//SDL_mutex* addDownKeysMutex = NULL;
	//SDL_mutex* heldKeysEraseMutex = NULL;
	//SDL_mutex* eraseDownKeysMutex = NULL;
	//
	//SDL_mutex* isKeyDownMutex = NULL;
	//SDL_mutex* isKeyHeldMutex = NULL;
	//SDL_mutex* isKeyUpMutex = NULL;

	static bool instanceFlag;
	static InputManager *instance;
};

#endif