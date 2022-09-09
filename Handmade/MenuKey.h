#pragma once
#include <string>
#include <vector>
#include "GameObject.h"
#include "Text.h"

class MenuKey : public GameObject
{

public:

	enum class Alignment
	{
		Centre,
		Bottom,
		Left,
		Right
	};

	enum class Index
	{
		Index_1,
		Index_2,
		Index_3,
		Index_4,
		Index_5,
		None = -1
	};

	MenuKey(const std::string& filename = "",
		Alignment alignment = Alignment::Centre,
		int itemTotal = 2,
		int charWidth = 25,
		int charHeight = 53,
		int padding = 10);

	virtual ~MenuKey();

	Index GetMenuChoice() const;

	void SetActiveColor(Uint8 r, Uint8 g, Uint8 b);
	void SetInactiveColor(Uint8 r, Uint8 g, Uint8 b);
	void SetMenuText(Index index, const std::string& text);

	void Update(int deltaTime) override;
	bool Render() override;

	void Reset();

private:

	std::string fontID;
	Alignment alignment;

	SDL_Point charDimension;
	SDL_Color activeColor{ 240, 0, 0 };
	SDL_Color inactiveColor{ 255, 255, 255 };

	std::vector<Text> menuItems;
	Index menuActive{ Index::Index_1 };
	Index menuChoice{ Index::None };

};