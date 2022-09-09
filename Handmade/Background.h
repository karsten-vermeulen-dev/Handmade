#pragma once
#include "GameObject.h"
#include "Music.h"
#include "Texture.h"

class Background : public GameObject
{

public:

	Background() {}
	virtual ~Background();

	void Load(const std::string& imageFilename,
		const std::string& audioFilename);
	void PlayMusic();
	void StopMusic();

	virtual void Update(int deltaTime) {}
	virtual bool Render();

protected:

	std::string imageID;
	std::string audioID;
	bool isPlaying{ false };

	Music music;
	Texture image;

};