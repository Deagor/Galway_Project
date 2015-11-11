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

	static bool instanceFlag;
	static InputManager *instance;
};

#endif