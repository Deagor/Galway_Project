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
	int downKeySize = downKeys.size();
	//Check for keys that were pressed in previous frame
	if (downKeySize > 0)
	{
		for (int i = --downKeySize; i >= 0; i--)
		{
			heldKeys.push_back(downKeys[i]);
			downKeys.erase(--downKeys.end());
		}
	}

	if (heldKeys.size() > 0)
	{
		//std::cout << "Key Held\n";
	}
}

void InputManager::UpdatePolledEvents(SDL_Event e)
{
	//if a new key was pressed
	if (!IsKeyHeld(e.key.keysym.sym))
	{
		if (e.type == SDL_KEYDOWN)
		{
			std::cout << "Key Pressed\n";
			downKeys.push_back(e.key.keysym.sym);
		}
	}

	//If a key was released
	if (e.type == SDL_KEYUP)
	{
		std::cout << "Key Released\n";
		heldKeys.erase(std::remove(heldKeys.begin(), heldKeys.end(), e.key.keysym.sym));
	}

	if (e.type == SDL_MOUSEBUTTONDOWN)
	{
		std::cout << "Mouse Clicked\n";

	}
}

bool InputManager::IsKeyDown(SDL_Keycode key)
{
	SDL_LockMutex(processMutex);
	auto iter = std::find(downKeys.begin(), downKeys.end(), key);

	if (iter != downKeys.end()) {
		return true;
	}
	SDL_UnlockMutex(processMutex);

	return false;
}

bool InputManager::IsKeyHeld(SDL_Keycode key)
{
	SDL_LockMutex(processMutex);
	auto iter = std::find(heldKeys.begin(), heldKeys.end(), key);

	if (iter != heldKeys.end())
	{
		return true;
	}
	SDL_UnlockMutex(processMutex);

	return false;
}

bool InputManager::IsKeyUp(SDL_Keycode key)
{
	SDL_LockMutex(processMutex);
	auto iter = std::find(upKeys.begin(), upKeys.end(), key);
	
	if (iter != upKeys.end())
	{
		return true;
	}
	SDL_UnlockMutex(processMutex);

	return false;
}