#include "StartState.h"
#include "PlayState.h"

//======================================================================================================
bool StartState::OnEnter()
{
	image.Load("Backgrounds/Menu_1280x720.png", "Journeys.ogg");
	menu = std::make_unique<MenuKey>("Quikhand.ttf", MenuKey::Alignment::Bottom);
	menu->SetMenuText(MenuKey::Index::Index_1, "Play game");
	menu->SetMenuText(MenuKey::Index::Index_2, "Quit game");

	return true;
}
//======================================================================================================
GameState* StartState::Update(int deltaTime)
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
bool StartState::Render()
{
	image.Render();
	menu->Render();
	return true;
}
//======================================================================================================
void StartState::OnExit()
{
	//Add shutdown tasks here
}