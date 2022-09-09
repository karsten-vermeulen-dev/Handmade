#pragma once
#include <map>
#include <memory>
#include <string>
#include <SDL_render.h>

typedef std::map<std::string, SDL_Texture*> Textures;

class Texture
{

public:

	enum class Flip
	{
		None = SDL_FLIP_NONE,
		Vertical = SDL_FLIP_VERTICAL,
		Horizontal = SDL_FLIP_HORIZONTAL
	};

	static bool Load(const std::string& filename, const std::string& tag);
	static void Unload(const std::string& tag = "");

	Texture() {}

	bool IsAnimationDead();
	void IsAnimated(bool flag);
	bool IsAnimationLooping();
	void IsAnimationLooping(bool flag);

	bool SetTexture(const std::string& tag);
	void SetCel(int column, int row);
	void SetAnimationVelocity(float velocity);
	void SetDimension(int width, int height);
	void SetSourceDimension(int columns, int rows, int width, int height);

	void ResetAnimation();
	void Update(int deltaTime);

	void Render(int x = 0,
		int y = 0,
		double angle = 0.0,
		Flip flip = Flip::None);

private:

	int cel{ 0 };
	float animationVelocity{ 0.0f };
	float animationRunningTime{ 0.0f };

	bool isAnimated{ false };
	bool isAnimationDead{ false };
	bool isAnimationLooping{ true };
	bool isAnimationLoopFinal{ false };

	SDL_Texture* texture{ nullptr };
	SDL_Point celDimension = { 0, 0 };
	SDL_Point sourceDimension = { 1, 1 };
	SDL_Point textureDimension = { 0, 0 };

	static std::string rootFolder;
	static std::unique_ptr<Textures> textures;

};