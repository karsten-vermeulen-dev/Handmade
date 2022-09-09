#pragma once

//TODO - Add default screens for each game state
//TODO - Cannot load resources in game states ctor
//TODO - Consider RAII to load/release resources in the ctor/dtor
//This would remove the need for OnEnter/OnExit?

class GameState
{

public:

	GameState() {}
	virtual ~GameState() = 0 {}

	bool IsAlive() const;
	bool IsActive() const;

	void IsAlive(bool flag);
	void IsActive(bool flag);

	virtual bool OnEnter() = 0;
	virtual GameState* Update(int deltaTime) = 0;
	virtual bool Render() = 0;
	virtual void OnExit() = 0;

private:

	//TODO - Fix this later
	bool isAlive{ true };
	bool isActive{ true };
	GameState* previousState{ nullptr };

};