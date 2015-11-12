#ifndef AUDIOMANGER
#define AUDIOMANGER

class AudioManager {
private:
	AudioManager();
	~AudioManager();
	Mix_Chunk *shoot_sfx;
	Mix_Chunk *jump_sfx;
	Mix_Chunk *hit_sfx;


public:
	static AudioManager* GetInstance();
	
	void Init();
	void LoadMedia();
	void PlaySoundEffect(int effect);
};
#endif