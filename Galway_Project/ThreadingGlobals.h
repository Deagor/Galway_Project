#pragma once
#include "stdafx.h"

//variables being used by threads globally
SDL_mutex* gInputManagerLock[2] = { NULL, NULL };

SDL_cond* gCanProduce = NULL;
SDL_cond* gCanConsume = NULL;