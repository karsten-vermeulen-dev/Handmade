#include <assert.h>
#include "Screen.h"
#include "Text.h"
#include "Utility.h"

std::string Text::rootFolder = "Assets/Fonts/";
std::unique_ptr<Fonts> Text::fonts = std::make_unique<Fonts>();

//======================================================================================================
bool Text::Initialize()
{
	if (TTF_Init() == -1)
	{
		Utility::Log(Utility::Destination::WindowsMessageBox,
			"Error initializing the font sub-system.", Utility::Severity::Failure);
		return false;
	}

	return true;
}
//======================================================================================================
bool Text::Load(const std::string& filename, const std::string& tag, FontSize fontSize)
{
	assert(fonts->find(tag) == fonts->end());

	TTF_Font* font = TTF_OpenFont((rootFolder + filename).c_str(), static_cast<int>(fontSize));

	if (!font)
	{
		Utility::Log(Utility::Destination::WindowsMessageBox,
			"Error loading font file \"" + (rootFolder + filename) + "\"\n\n"
			"Possible causes could be a corrupt or missing file. Another reason could be "
			"that the filename and/or path are incorrectly spelt.", Utility::Severity::Failure);
		return false;
	}

	fonts->insert(std::pair<std::string, TTF_Font*>(tag, font));
	return true;
}
//======================================================================================================
void Text::Unload(const std::string& tag)
{
	if (!tag.empty())
	{
		auto it = fonts->find(tag);
		assert(it != fonts->end());
		TTF_CloseFont(it->second);
		fonts->erase(it);
	}

	else
	{
		for (const auto& font : *fonts)
		{
			TTF_CloseFont(font.second);
		}

		fonts->clear();
	}
}
//======================================================================================================
void Text::Shutdown()
{
	TTF_Quit();
}
//======================================================================================================
Text::Text(const Text& copy)
{
	texture = nullptr;
	font = copy.font;
	color = copy.color;
	string = copy.string;
	textSize = copy.textSize;
	isDirty = true;
}
//======================================================================================================
Text::~Text()
{
	SDL_DestroyTexture(texture);
}
//======================================================================================================
const SDL_Point& Text::GetSize() const
{
	return textSize;
}
//======================================================================================================
const std::string& Text::GetString() const
{
	return string;
}
//======================================================================================================
void Text::SetSize(int width, int height)
{
	textSize.x = width;
	textSize.y = height;
}
//======================================================================================================
void Text::SetString(const std::string& string)
{
	this->string = string;
	isDirty = true;
}
//======================================================================================================
void Text::SetColor(Uint8 r, Uint8 g, Uint8 b)
{
	color.r = r;
	color.g = g;
	color.b = b;
	isDirty = true;
}
//======================================================================================================
bool Text::SetFont(const std::string& tag)
{
	auto it = fonts->find(tag);
	assert(it != fonts->end());
	font = (*it).second;
	isDirty = true;
	return true;
}
//======================================================================================================
void Text::Render(int x, int y)
{
	SDL_Rect dst;

	dst.x = x;
	dst.y = y;
	dst.w = textSize.x;
	dst.h = textSize.y;

	if (isDirty)
	{
		CreateText();
		isDirty = false;
	}

	SDL_RenderCopy(Screen::Instance()->GetRenderer(), texture, nullptr, &dst);
}
//======================================================================================================
void Text::CreateText()
{
	assert(font != nullptr);
	SDL_Surface* textSurface = TTF_RenderText_Blended(font, string.c_str(), color);

	SDL_DestroyTexture(texture);
	texture = SDL_CreateTextureFromSurface(Screen::Instance()->GetRenderer(), textSurface);

	SDL_FreeSurface(textSurface);
}