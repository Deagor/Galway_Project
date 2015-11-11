#include "stdafx.h"
#include "AudioManager.h"

Mix_Chunk *step_sfx = NULL;
Mix_Chunk *jump_sfx = NULL;
Mix_Chunk *pickUp_sfx = NULL;
Mix_Chunk *rewindTime_sfx = NULL;

AudioManager::AudioManager(){

}

void AudioManager::Init()
{
	//Initialize SDL
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

	//Initialize SDL_mixer
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
}

void AudioManager::LoadMedia()
{
	//Load sound effects
	step_sfx = Mix_LoadWAV("step.wav");
	jump_sfx = Mix_LoadWAV("jump.wav");
	pickUp_sfx = Mix_LoadWAV("pickup.wav");
	rewindTime_sfx = Mix_LoadWAV("rewind.wav");
}

void AudioManager::PlaySoundEffect(int effect){
	if (effect == 1)
	{
		Mix_PlayChannel(-1, step_sfx, 0);
	}
	else if (effect == 2)
	{
		Mix_PlayChannel(-1, jump_sfx, 0);
	}
	if (effect == 3)
	{
		Mix_PlayChannel(-1, pickUp_sfx, 0);
	}
	else if (effect == 4)
	{
		Mix_PlayChannel(-1, rewindTime_sfx, 0);
	}
}