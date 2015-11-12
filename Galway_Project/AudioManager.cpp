#include "stdafx.h"
#include "AudioManager.h"

static bool instanceFlag = false;
static AudioManager* instance = NULL;

AudioManager* AudioManager::GetInstance()
{
	if (!instanceFlag)
	{
		instance = new AudioManager();
		instanceFlag = true;
		return instance;
	}
	else
	{
		return instance;
	}
}

AudioManager::AudioManager()
{
	shoot_sfx = NULL;
	jump_sfx = NULL;
	hit_sfx = NULL;
}

void AudioManager::Init()
{
	//Initialize SDL
	SDL_Init(SDL_INIT_AUDIO);

	//Initialize SDL_mixer
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
}

void AudioManager::LoadMedia()
{
	std::string basepath(SDL_GetBasePath());
	std::string jumpPath = basepath + "../Sounds/jump.wav";
	std::string shootPath = basepath + "../Sounds/shoot.wav";
	std::string hitPath = basepath + "../Sounds/hitSound.wav";

	//Load sound effects
	jump_sfx = Mix_LoadWAV(jumpPath.c_str());
	shoot_sfx = Mix_LoadWAV(shootPath.c_str());
	hit_sfx = Mix_LoadWAV(hitPath.c_str());
}

void AudioManager::PlaySoundEffect(int effect){
	if (effect == 1)//shoot
	{
		Mix_PlayChannel(-1, shoot_sfx, 0);
	}
	else if (effect == 2)//jump
	{
		Mix_PlayChannel(-1, jump_sfx, 0);
	}
	if (effect == 3)//hit
	{
		Mix_PlayChannel(-1, hit_sfx, 0);
	}
}

AudioManager::~AudioManager()
{
	instanceFlag = false;
}
