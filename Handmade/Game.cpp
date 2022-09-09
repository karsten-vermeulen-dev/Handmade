#include "Game.h"
#include "Input.h"
#include "Music.h"
#include "Screen.h"
#include "Text.h"
#include "Utility.h"

//======================================================================================================
Game::Game(GameState* initialGameState)
{
	gameState.reset(initialGameState);
}
//======================================================================================================
bool Game::Initialize(const std::string& name, int screenWidth, int screenHeight, bool fullscreen)
{
	if (!Screen::Instance()->Initialize(name.c_str(), screenWidth, screenHeight, fullscreen))
	{
		return false;
	}

	Screen::Instance()->SetClearColor(100, 149, 237);

	if (!(Music::Initialize()))
	{
		//Not serious - game does not need to end
		//Add your own outcome/messages here...
	}

	if (!Text::Initialize())
	{
		//Not serious - game does not need to end
		//Add your own outcome/messages here...
	}

	Utility::SetWindowHandle(Screen::Instance()->GetWindowHandle());
	return true;
}
//======================================================================================================
void Game::AddState(GameState* state)
{
	//TODO - Fix this later
	//state->OnEnter();
	//gameStates.push_front(state);
}
//======================================================================================================
void Game::ChangeState(GameState* state)
{
	//TODO - Fix this later
	//state->OnEnter();
	//gameStates.push_back(state);
}
//======================================================================================================
bool Game::Run()
{
	gameState->OnEnter();

	while (gameState)
	{
		//TODO - Fix this later
		//The current active state is always the front one
		//state = gameStates.front();

		int startTime = SDL_GetTicks();

		Screen::Instance()->Clear();
		Input::Instance()->Update();

		GameState* nextState = gameState->Update(deltaTime);

		gameState->Render();

		Screen::Instance()->Present();

		if (nextState != gameState.get())
		{
			gameState->OnExit();
			gameState.reset(nextState);

			if (gameState)
			{
				gameState->OnEnter();
			}
		}

		deltaTime = SDL_GetTicks() - startTime;

		//TODO - Fix this later
		//The main game loop will run as long there are game states available
		//endGame = gameStates.empty();
	}

	//TODO - Fix this later
	//If game state is also flagged as dead  
	//then completely remove all of its objects
	/*if (!state->IsAlive())
	{
		RemoveState();
	}*/

	return true;
}
//======================================================================================================
void Game::Shutdown()
{
	Text::Shutdown();
	Music::Shutdown();
	Screen::Instance()->Shutdown();
}
//======================================================================================================
void Game::RemoveState()
{
	//TODO - Fix this later
	/*gameStates.front()->OnExit();
	delete gameStates.front();
	gameStates.pop_front();*/
}