#include "Background.h"
#include "Screen.h"
#include "Vector.h"

//======================================================================================================
Background::~Background()
{
	music.Unload(audioID);
	image.Unload(imageID);
}
//======================================================================================================
bool Background::Render()
{
	image.Render();
	return true;
}
//======================================================================================================
void Background::Load(const std::string& imageFilename, const std::string& audioFilename)
{
	auto resolution = Screen::Instance()->GetResolution();

	image.Load(imageFilename, imageFilename);
	image.SetTexture(imageFilename);
	image.SetDimension(resolution.x, resolution.y);
	image.SetSourceDimension(1, 1, resolution.x, resolution.y);

	music.Load(audioFilename, audioFilename);
	music.SetMusic(audioFilename);
	music.SetVolume(0.5f);

	imageID = imageFilename;
	audioID = audioFilename;
}
//======================================================================================================
void Background::PlayMusic()
{
	if (!isPlaying)
	{
		music.Play(Music::Loop::Ongoing);
		isPlaying = true;
	}
}
//======================================================================================================
void Background::StopMusic()
{
	music.Stop();
	isPlaying = false;
}