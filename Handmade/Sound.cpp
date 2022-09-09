#include <algorithm>
#include <assert.h>
#include "Sound.h"
#include "Utility.h"

std::string Sound::rootFolder = "Assets/Sounds/";
std::unique_ptr<Sounds> Sound::sounds = std::make_unique<Sounds>();

//======================================================================================================
bool Sound::Load(const std::string& filename, const std::string& tag)
{
	assert(sounds->find(tag) == sounds->end());

	Mix_Chunk* sound = Mix_LoadWAV((rootFolder + filename).c_str());

	if (!sound)
	{
		Utility::Log(Utility::Destination::WindowsMessageBox,
			"Error loading sound file \"" + (rootFolder + filename) + "\"\n\n"
			"Possible causes could be a corrupt or missing file. Another reason could be "
			"that the filename and/or path are incorrectly spelt.", Utility::Severity::Failure);
		return false;
	}

	sounds->insert(std::pair<std::string, Mix_Chunk*>(tag, sound));
	return true;
}
//======================================================================================================
void Sound::Unload(const std::string& tag)
{
	if (!tag.empty())
	{
		auto it = sounds->find(tag);
		assert(it != sounds->end());
		Mix_FreeChunk(it->second);
		sounds->erase(it);
	}

	else
	{
		for (const auto& sound : *sounds)
		{
			Mix_FreeChunk(sound.second);
		}

		sounds->clear();
	}
}
//======================================================================================================
void Sound::SetVolume(float volume)
{
	volume = std::clamp(volume, 0.0f, 1.0f);
	Mix_VolumeChunk(sound, static_cast<int>(volume * 128.0f));
}
//======================================================================================================
bool Sound::SetSound(const std::string& tag)
{
	auto it = sounds->find(tag);
	assert(it != sounds->end());
	sound = (*it).second;
	return true;
}
//======================================================================================================
bool Sound::Play(int loop)
{
	if (Mix_PlayChannel(-1, sound, loop) == -1)
	{
		Utility::Log(Utility::Destination::WindowsMessageBox,
			"Sound could not be played.", Utility::Severity::Failure);
		return false;
	}

	return true;
}