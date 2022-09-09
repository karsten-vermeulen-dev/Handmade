#pragma once
#include <deque>
#include <memory>
#include <string>
#include "GameState.h"

class Game
{

public:

	Game(GameState* initialGameState);

	bool Initialize(const std::string& name,
		int screenWidth,
		int screenHeight,
		bool fullscreen = false);

	void AddState(GameState* state);
	void ChangeState(GameState* state);

	bool Run();
	void Shutdown();

private:

	void RemoveState();

	int deltaTime{ 0 };
	//std::deque<GameState*> m_gameStates;
	std::unique_ptr<GameState> gameState;

};