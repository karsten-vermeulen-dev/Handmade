#include <algorithm>
#include <assert.h>
#include <SDL_image.h>
#include "Screen.h"
#include "Texture.h"
#include "Utility.h"

std::string Texture::rootFolder = "Assets/Textures/";
std::unique_ptr<Textures> Texture::textures = std::make_unique<Textures>();

//======================================================================================================
bool Texture::Load(const std::string& filename, const std::string& tag)
{
	assert(textures->find(tag) == textures->end());

	SDL_Surface* imageData = IMG_Load((rootFolder + filename).c_str());

	if (!imageData)
	{
		Utility::Log(Utility::Destination::WindowsMessageBox,
			"Error loading image file \"" + (rootFolder + filename) + "\"\n\n"
			"Possible causes could be a corrupt or missing file. Another reason could be "
			"that the filename and/or path are incorrectly spelt.", Utility::Severity::Failure);
		return false;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(Screen::Instance()->GetRenderer(), imageData);
	SDL_FreeSurface(imageData);

	textures->insert(std::pair<std::string, SDL_Texture*>(tag, texture));
	return true;
}
//======================================================================================================
void Texture::Unload(const std::string& tag)
{
	if (!tag.empty())
	{
		auto it = textures->find(tag);
		assert(it != textures->end());
		SDL_DestroyTexture(it->second);
		textures->erase(it);
	}

	else
	{
		for (const auto& texture : *textures)
		{
			SDL_DestroyTexture(texture.second);
		}

		textures->clear();
	}
}
//======================================================================================================
bool Texture::IsAnimationDead()
{
	return isAnimationDead;
}
//======================================================================================================
void Texture::IsAnimated(bool flag)
{
	isAnimated = flag;
}
//======================================================================================================
bool Texture::IsAnimationLooping()
{
	return isAnimationLooping;
}
//======================================================================================================
void Texture::IsAnimationLooping(bool flag)
{
	isAnimationLooping = flag;
}
//======================================================================================================
void Texture::SetCel(int column, int row)
{
	//Make sure this function is called AFTER calling 'SetSourceDimension()'
	//You cannot use zero-based, negative or larger indices than the texture atlas allows
	assert(column > 0 && column <= sourceDimension.x);
	assert(row > 0 && row <= sourceDimension.y);
	cel = ((row - 1) * sourceDimension.x) + (column - 1);
}
//======================================================================================================
void Texture::SetAnimationVelocity(float velocity)
{
	assert(velocity >= 0.0f);
	animationVelocity = velocity;
}
//======================================================================================================
bool Texture::SetTexture(const std::string& tag)
{
	auto it = textures->find(tag);
	assert(it != textures->end());
	texture = (*it).second;
	return true;
}
//======================================================================================================
void Texture::SetDimension(int width, int height)
{
	assert(width > 0 && height > 0);
	textureDimension.x = width;
	textureDimension.y = height;
}
//======================================================================================================
void Texture::SetSourceDimension(int columns, int rows, int width, int height)
{
	assert(rows > 0 && columns > 0 && width > 0 && height > 0);

	sourceDimension.x = columns;
	sourceDimension.y = rows;

	celDimension.x = width / columns;
	celDimension.y = height / rows;
}
//======================================================================================================
void Texture::ResetAnimation()
{
	cel = 0;
	isAnimationDead = false;
	animationRunningTime = 0.0f;
	isAnimationLoopFinal = false;
}
//======================================================================================================
void Texture::Update(int deltaTime)
{
	//If sprite is an animation we have to calculate the 
	//image cel each frame because it won't be a static value
	if (isAnimated)
	{
		animationRunningTime += deltaTime / 1000.0f;

		//Aquire index value of specific texture cel to 'cut out' using a formula
		//The image index is zero-based and is a whole number value counting from
		//top left and going right and down the sprite sheet, and is capable of 'wrapping'
		cel = static_cast<int>(animationRunningTime * animationVelocity) %
			static_cast<int>(sourceDimension.x * sourceDimension.y);

		if (isAnimationLooping)
		{
			isAnimationDead = false;
			isAnimationLoopFinal = false;
		}

		//If animation is set to cycle once and the last image cel 
		//has been reached then flag this as the final animation loop
		else if (!isAnimationLooping &&
			cel == (sourceDimension.x * sourceDimension.y - 1))
		{
			isAnimationLoopFinal = true;
		}

		//If this is the final animation, flag to kill entire animation
		//because even though the animation is marked final, a few more 
		//frames will be called with the last image cel set, so only
		//mark it dead when the first image cel comes around again
		if (isAnimationLoopFinal && cel == 0)
		{
			isAnimationDead = true;
		}
	}
}
//======================================================================================================
void Texture::Render(int x, int y, double angle, Flip flip)
{
	//Make sure you call 'SetTexture()' after loading the texture
	assert(texture != nullptr);

	//Make sure you call 'SetSourceDimension()'
	assert(celDimension.x > 0 && celDimension.y > 0);

	//Make sure you call 'SetDimension()'
	assert(textureDimension.x > 0 && textureDimension.y > 0);

	if (!isAnimationDead)
	{
		//Variables to store rectangular dimensions for the source 
		//sprite and destination portion of the screen to render to 
		SDL_Rect src;
		SDL_Rect dst;

		//We need to get exact cel block xy coordinates to 'cut out' 
		src.x = (cel % sourceDimension.x) * celDimension.x;
		src.y = (cel / sourceDimension.x) * celDimension.y;
		src.w = celDimension.x;
		src.h = celDimension.y;

		dst.x = x;
		dst.y = y;
		dst.w = textureDimension.x;
		dst.h = textureDimension.y;

		//Use the centre of the sprite as its centre of rotation
		SDL_Point centrePoint;
		centrePoint.x = textureDimension.x / 2;
		centrePoint.y = textureDimension.y / 2;

		SDL_RenderCopyEx(Screen::Instance()->GetRenderer(),
			texture, &src, &dst, angle, &centrePoint, static_cast<SDL_RendererFlip>(flip));
	}
}