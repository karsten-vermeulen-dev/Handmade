#include "EndState.h"
#include "Input.h"
#include "StartState.h"
#include "PlayState.h"

//======================================================================================================
bool PlayState::OnEnter()
{
	image.Load("Backgrounds/Play_1280x720.png", "Aircord.ogg");
	return true;
}
//======================================================================================================
GameState* PlayState::Update(int deltaTime)
{
	image.PlayMusic();

	if (Input::Instance()->IsKeyPressed(HM_KEY_M))
	{
		image.StopMusic();
		return new StartState;
	}

	if (Input::Instance()->IsKeyPressed(HM_KEY_Q))
	{
		image.StopMusic();
		return new EndState;
	}

	for (auto& gameObject : gameObjects)
	{
		if (gameObject.IsActive())
		{
			gameObject.Update(deltaTime);
		}
	}

	return this;
}
//======================================================================================================
bool PlayState::Render()
{
	image.Render();

	for (auto& gameObject : gameObjects)
	{
		if (gameObject.IsActive() && gameObject.IsVisible())
		{
			gameObject.Render();
		}
	}

	return true;
}
//======================================================================================================
void PlayState::OnExit()
{
	gameObjects.clear();
}