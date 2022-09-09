#include "EndState.h"
#include "PlayState.h"

//======================================================================================================
bool EndState::OnEnter()
{
	image.Load("Backgrounds/End_1280x720.png", "Glory.ogg");
	menu = std::make_unique<MenuKey>("Quikhand.ttf", MenuKey::Alignment::Bottom);
	menu->SetMenuText(MenuKey::Index::Index_1, "Play again");
	menu->SetMenuText(MenuKey::Index::Index_2, "Quit game");

	return true;
}
//======================================================================================================
GameState* EndState::Update(int deltaTime)
{
	image.PlayMusic();
	menu->Update(deltaTime);

	if (menu->GetMenuChoice() == static_cast<MenuKey::Index>(MenuOption::Play))
	{
		image.StopMusic();
		return new PlayState;
	}

	if (menu->GetMenuChoice() == static_cast<MenuKey::Index>(MenuOption::Quit))
	{
		image.StopMusic();
		return nullptr;
	}

	return this;
}
//======================================================================================================
bool EndState::Render()
{
	image.Render();
	menu->Render();
	return true;
}
//======================================================================================================
void EndState::OnExit()
{
	//Add shutdown tasks here
}