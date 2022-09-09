#include "Input.h"
#include "MenuKey.h"
#include "Screen.h"
#include "Vector.h"

//======================================================================================================
MenuKey::MenuKey(const std::string& filename,
	Alignment alignment,
	int itemTotal,
	int charWidth,
	int charHeight,
	int padding) : fontID(filename), alignment(alignment)
{
	charDimension.x = charWidth;
	charDimension.y = charHeight;

	auto resolution = Screen::Instance()->GetResolution();

	//This will position the text dead centre in the middle of the screen
	//X - Divide screen width in half and subtract half the width of each text
	//Y - Divide screen height in half and subtract half of the menu's text heights
	if (alignment == Alignment::Centre)
	{
		position.x = resolution.x / 2;
		position.y = static_cast<int>((resolution.y / 2) - (itemTotal / 2.0f * charHeight));
	}

	//This will position the text in the bottom half of the screen, centered in X
	//X - Divide screen width in half and subtract half the width of each text
	//Y - Divide screen height in quarters and subtract half of the menu's text heights
	else if (alignment == Alignment::Bottom)
	{
		position.x = resolution.x / 2;
		position.y = static_cast<int>((resolution.y - resolution.y / 4) - (itemTotal / 2.0f * charHeight));
	}

	//This will position the text in the bottom half of the screen, aligned on the left
	//X - Position the origin on the very left and add on some padding based on passed value
	//Y - Divide the screen height in quarters and subtract half of the menu's text heights
	else if (alignment == Alignment::Left)
	{
		position.x += padding;
		position.y = static_cast<int>((resolution.y - resolution.y / 4) - (itemTotal / 2.0f * charHeight));
	}

	//this will position the text in the bottom half of the screen, aligned on the right
	//X - position the origin on the very right and add on some padding based on passed value
	//Y - divide the screen height in quarters and subtract half of the menu's text heights
	else if (alignment == Alignment::Right)
	{
		position.x = resolution.x - padding;
		position.y = static_cast<int>((resolution.y - resolution.y / 4) - (itemTotal / 2.0f * charHeight));
	}

	//pre-load text objects into memory
	for (int i = 0; i < itemTotal; i++)
	{
		menuItems.push_back(Text());
	}

	Text::Load(filename, "MenuFont");
}
//======================================================================================================
MenuKey::~MenuKey()
{
	menuItems.clear();
	Text::Unload("MenuFont");
}
//======================================================================================================
MenuKey::Index MenuKey::GetMenuChoice() const
{
	return menuChoice;
}
//======================================================================================================
void MenuKey::SetActiveColor(Uint8 r, Uint8 g, Uint8 b)
{
	activeColor = { r, g, b };
}
//======================================================================================================
void MenuKey::SetInactiveColor(Uint8 r, Uint8 g, Uint8 b)
{
	inactiveColor = { r, g, b };
}
//======================================================================================================
void MenuKey::SetMenuText(Index index, const std::string& text)
{
	menuItems[static_cast<int>(index)].SetFont("MenuFont");
	menuItems[static_cast<int>(index)].SetString(text);
	menuItems[static_cast<int>(index)].SetSize(text.size() * charDimension.x, charDimension.y);
	menuItems[static_cast<int>(index)].SetColor(inactiveColor.r, inactiveColor.g, inactiveColor.b);
}
//======================================================================================================
void MenuKey::Update(int deltaTime)
{
	//Flag to monitor if key is pressed so that when pressing UP/DOWN
	//key the selected menu option doesn't move at lightning speed
	static bool isKeyPressed = false;

	//Only if DOWN arrow key is pressed and key was not pressed before move one option down the menu
	//Also check if the last menu item has been reached, which means we need to loop back to the top
	if (Input::Instance()->IsKeyPressed(HM_KEY_DOWN) && !isKeyPressed)
	{
		if (menuActive == static_cast<Index>(menuItems.size() - 1))
		{
			menuActive = Index::Index_1;
		}

		else
		{
			menuActive = static_cast<Index>(static_cast<int>(menuActive) + 1);
		}

		isDirty = true;
	}

	//Only if UP arrow key is pressed and key was not pressed before move one option up the menu
	//Also check if the first menu item has been reached, which means we need to go to the bottom
	if (Input::Instance()->IsKeyPressed(HM_KEY_UP) && !isKeyPressed)
	{
		if (menuActive == Index::Index_1)
		{
			menuActive = static_cast<Index>(menuItems.size() - 1);
		}

		else
		{
			menuActive = static_cast<Index>(static_cast<int>(menuActive) - 1);
		}

		isDirty = true;
	}

	if (Input::Instance()->IsKeyPressed(HM_KEY_RETURN))
	{
		menuChoice = menuActive;
	}

	//Update state of key based on if it's pressed or not which will make sure the next time
	//the frame is called the above code will either move the menu option or keep it still
	isKeyPressed = Input::Instance()->IsKeyPressed();

	if (isDirty)
	{
		for (size_t i = 0; i < menuItems.size(); i++)
		{
			menuItems[i].SetColor(inactiveColor.r, inactiveColor.g, inactiveColor.b);
		}

		menuItems[static_cast<int>(menuActive)].SetColor(activeColor.r, activeColor.g, activeColor.b);

		isDirty = false;
	}
}
//======================================================================================================
bool MenuKey::Render()
{
	//Loop through all menu items and position them based on the x and y positional origin
	//Check what menu style is set so that we can determine where on-screen to render the text

	for (size_t i = 0; i < menuItems.size(); i++)
	{
		if (alignment == Alignment::Centre || alignment == Alignment::Bottom)
		{
			menuItems[i].Render(position.x - (menuItems[i].GetSize().x / 2),      //x
				position.y + (i * menuItems[i].GetSize().y));					  //y
		}

		else if (alignment == Alignment::Left)
		{
			menuItems[i].Render(position.x,                                       //x
				position.y + (i * menuItems[i].GetSize().y));					  //y
		}

		else if (alignment == Alignment::Right)
		{
			menuItems[i].Render(position.x - menuItems[i].GetSize().x,            //x
				position.y + (i * menuItems[i].GetSize().y));					  //y
		}
	}

	return true;
}
//======================================================================================================
void MenuKey::Reset()
{
	menuActive = Index::Index_1;
	menuChoice = Index::None;
}