// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include "SDL.h"

#include "Build\Box2D.h"

#include <stdio.h>
#include <tchar.h>
#include <vector>
#include <list>
#include <sstream>
#include <string>
#include <algorithm>
#include <iostream>
#include <chrono>
#include <thread>        
#include <queue> 
#include <functional>

#include <SDL_mixer.h>

#include "InputManager.h"
#include "Render.h"
#include "Player.h" 
#include "Enemy.h"
#include "EnemyManager.h"
#include "Platform.h"
#include "Bullet.h"
#include "AudioManager.h"
#include "ContactListener.h"
#include "LevelManager.h"
#include "BodyDestroyer.h" 

#include "ThreadingGlobals.h"

#include <SDL.h>
#include <SDL_ttf.h> 

#include "LTimer.h"

using namespace std;
// TODO: reference additional headers your program requires here
