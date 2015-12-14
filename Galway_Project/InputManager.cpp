#include "stdafx.h"
#include "InputManager.h"

bool InputManager::instanceFlag = false;
InputManager* InputManager::instance = NULL;

SDL_mutex* heldKeysPushBackMutex = SDL_CreateMutex();
SDL_mutex* addDownKeysMutex = SDL_CreateMutex();
SDL_mutex* heldKeysEraseMutex = SDL_CreateMutex();
SDL_mutex* eraseDownKeysMutex = SDL_CreateMutex();

SDL_mutex* isKeyDownMutex = SDL_CreateMutex();
SDL_mutex* isKeyHeldMutex = SDL_CreateMutex();
SDL_mutex* isKeyUpMutex = SDL_CreateMutex();

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
			heldKeysPushBack(downKeys[i]);
			downKeysErase();
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
			downKeysPushBack(e.key.keysym.sym);
		}
	}

	//If a key was released
	if (e.type == SDL_KEYUP)
	{
		std::cout << "Key Released\n";
		heldKeysErase(e.key.keysym.sym);
	}
	/*SDL_UnlockMutex(heldKeysEraseMutex);*/

	if (e.type == SDL_MOUSEBUTTONDOWN)
	{
		std::cout << "Mouse Clicked\n";

	}
}

void InputManager::downKeysPushBack(SDL_Keycode k)
{
	if (addDownKeysMutex != 0)
	{
		SDL_LockMutex(addDownKeysMutex);
		downKeys.push_back(k);
		SDL_UnlockMutex(addDownKeysMutex);
	}
}

void InputManager::downKeysErase()
{
	if (eraseDownKeysMutex != 0)
	{
		SDL_LockMutex(eraseDownKeysMutex);
		downKeys.erase(--downKeys.end());
		SDL_UnlockMutex(eraseDownKeysMutex);
	}
}

void InputManager::heldKeysPushBack(SDL_Keycode k)
{
	if (heldKeysPushBackMutex != 0)
	{
		SDL_LockMutex(heldKeysPushBackMutex);
		heldKeys.push_back(k);
		SDL_UnlockMutex(heldKeysPushBackMutex);
	}
}

void InputManager::heldKeysErase(SDL_Keycode k)
{
	if (heldKeysEraseMutex != 0)
	{
		SDL_LockMutex(heldKeysEraseMutex);
		heldKeys.erase(std::remove(heldKeys.begin(), heldKeys.end(), k));
		SDL_UnlockMutex(heldKeysEraseMutex);
	}
}

bool InputManager::IsKeyDown(SDL_Keycode key)
{
	//SDL_LockMutex(isKeyDownMutex);
	auto iter = std::find(downKeys.begin(), downKeys.end(), key);

	if (iter != downKeys.end()) {
		return true;
	}
	//SDL_UnlockMutex(isKeyDownMutex);

	return false;
}

bool InputManager::IsKeyHeld(SDL_Keycode key)
{
	//SDL_LockMutex(isKeyHeldMutex);
	auto iter = std::find(heldKeys.begin(), heldKeys.end(), key);

	if (iter != heldKeys.end())
	{
		return true;
	}
	//SDL_UnlockMutex(isKeyHeldMutex);

	return false;
}

bool InputManager::IsKeyUp(SDL_Keycode key)
{
	//SDL_LockMutex(isKeyUpMutex);
	auto iter = std::find(upKeys.begin(), upKeys.end(), key);
	
	if (iter != upKeys.end())
	{
		return true;
	}
	//SDL_UnlockMutex(isKeyUpMutex);

	return false;
}