#pragma once
#include "stdafx.h"

//variables being used by threads globally
SDL_mutex* gInputManagerLock[2] = { NULL, NULL };

SDL_cond* InputCanProduce1 = NULL;
SDL_cond* InputCanProduce2 = NULL;

SDL_cond* InputCanConsume1 = NULL;
SDL_cond* InputCanConsume2 = NULL;