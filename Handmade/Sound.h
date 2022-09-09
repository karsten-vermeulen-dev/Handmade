#pragma once
#include <map>
#include <memory>
#include <string>
#include <SDL_mixer.h>

typedef std::map<std::string, Mix_Chunk*> Sounds;

class Sound
{

public:

	static bool Load(const std::string& filename, const std::string& tag);
	static void Unload(const std::string& tag = "");

	Sound() {}

	void SetVolume(float volume);
	bool SetSound(const std::string& tag);

	bool Play(int loop = 0);

private:

	Mix_Chunk* sound{ nullptr };

	static std::string rootFolder;
	static std::unique_ptr<Sounds> sounds;

};