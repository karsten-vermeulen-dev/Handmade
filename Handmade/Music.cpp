#include <algorithm>
#include <assert.h>
#include "Music.h"
#include "Utility.h"

std::string Music::rootFolder = "Assets/Music/";
std::unique_ptr<Musics> Music::musics = std::make_unique<Musics>();

//======================================================================================================
bool Music::Initialize(int frequency, int chunkSize)
{
	if (Mix_OpenAudio(frequency, AUDIO_S16SYS, 2, chunkSize) == -1)
	{
		Utility::Log(Utility::Destination::WindowsMessageBox,
			"Error initializing the audio sub-system.", Utility::Severity::Failure);
		return false;
	}

	return true;
}
//======================================================================================================
bool Music::Load(const std::string& filename, const std::string& tag)
{
	assert(musics->find(tag) == musics->end());

	Mix_Music* music = Mix_LoadMUS((rootFolder + filename).c_str());

	if (!music)
	{
		Utility::Log(Utility::Destination::WindowsMessageBox,
			"Error loading music file \"" + (rootFolder + filename) + "\"\n\n"
			"Possible causes could be a corrupt or missing file. Another reason could be "
			"that the filename and/or path are incorrectly spelt.", Utility::Severity::Failure);
		return false;
	}

	musics->insert(std::pair<std::string, Mix_Music*>(tag, music));
	return true;
}
//======================================================================================================
void Music::Unload(const std::string& tag)
{
	if (!tag.empty())
	{
		auto it = musics->find(tag);
		assert(it != musics->end());
		Mix_FreeMusic(it->second);
		musics->erase(it);
	}

	else
	{
		for (const auto& music : *musics)
		{
			Mix_FreeMusic(music.second);
		}

		musics->clear();
	}
}
//======================================================================================================
void Music::Shutdown()
{
	Mix_CloseAudio();
}
//======================================================================================================
void Music::SetVolume(float volume)
{
	volume = std::clamp(volume, 0.0f, 1.0f);
	Mix_VolumeMusic(static_cast<int>(volume * 128.0f));
}
//======================================================================================================
bool Music::SetMusic(const std::string& tag)
{
	auto it = musics->find(tag);
	assert(it != musics->end());
	music = (*it).second;
	return true;
}
//======================================================================================================
bool Music::Play(Loop loop)
{
	if (!Mix_PlayingMusic())
	{
		if (Mix_PlayMusic(music, static_cast<int>(loop)) == -1)
		{
			Utility::Log(Utility::Destination::WindowsMessageBox,
				"Music could not be played.", Utility::Severity::Failure);
			return false;
		}
	}

	return true;
}
//======================================================================================================
void Music::Pause()
{
	if (!Mix_PausedMusic())
	{
		Mix_PauseMusic();
	}
}
//======================================================================================================
void Music::Resume()
{
	if (Mix_PausedMusic())
	{
		Mix_ResumeMusic();
	}
}
//======================================================================================================
void Music::Stop()
{
	if (Mix_PlayingMusic())
	{
		Mix_HaltMusic();
	}
}