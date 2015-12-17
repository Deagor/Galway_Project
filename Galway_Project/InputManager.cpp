#include "stdafx.h"
#include "InputManager.h"

bool InputManager::instanceFlag = false;
InputManager* InputManager::instance = NULL;

InputManager* InputManager::GetInstance()
{
	if (!instanceFlag)
	{
		instance = new InputManager();
		instanceFlag = true;
		return instance;
	}
	else
	{
		return instance;
	}
}

void InputManager::UpdateKeyboardState()
{
	
	//Check for keys that were pressed in previous frame
    SDL_LockMutex(DownKeyMutex);

    auto downKeySnapShot = downKeys;

    SDL_UnlockMutex(DownKeyMutex);

    int downKeySize = downKeySnapShot.size();

	if (downKeySize > 0)
	{ 
		for (int i = --downKeySize; i >= 0; i--)
		{
            SDL_LockMutex(HeldKeyMutex);

			heldKeys.push_back(downKeySnapShot[i]);

            SDL_UnlockMutex(HeldKeyMutex);

            SDL_LockMutex(DownKeyMutex);

			downKeys.erase(--downKeys.end());
            downKeySnapShot.erase(--downKeySnapShot.end());

            SDL_UnlockMutex(DownKeyMutex);
		}
	}

    

}

void InputManager::UpdatePolledEvents(SDL_Event e)
{
	//if a new key was pressed
    SDL_LockMutex(HeldKeyMutex);

    bool isKeyHeldSnapShot = IsKeyHeld(e.key.keysym.sym);

    SDL_UnlockMutex(HeldKeyMutex);

	if (!isKeyHeldSnapShot)
	{
		if (e.type == SDL_KEYDOWN)
		{
			std::cout << "Key Pressed\n";

            SDL_LockMutex(DownKeyMutex);

			downKeys.push_back(e.key.keysym.sym);

            SDL_UnlockMutex(DownKeyMutex);
		}
	}
    
    

	//If a key was released
	if (e.type == SDL_KEYUP)
	{
		std::cout << "Key Released\n";

        SDL_LockMutex(HeldKeyMutex)
		heldKeys.erase(std::remove(heldKeys.begin(), heldKeys.end(), e.key.keysym.sym));
        SDL_UnlockMutex(HeldKeyMutex)
	}

}

bool InputManager::IsKeyDown(SDL_Keycode key)
{
	auto iter = std::find(downKeys.begin(), downKeys.end(), key);

	if (iter != downKeys.end()) {
		return true;
	}

	return false;
}

bool InputManager::IsKeyHeld(SDL_Keycode key)
{
	auto iter = std::find(heldKeys.begin(), heldKeys.end(), key);

	if (iter != heldKeys.end())
	{
		return true;
	}
	return false;
}

bool InputManager::IsKeyUp(SDL_Keycode key)
{
	auto iter = std::find(upKeys.begin(), upKeys.end(), key);
	
	if (iter != upKeys.end())
	{
		return true;
	}
	return false;
}