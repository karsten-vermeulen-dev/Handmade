#pragma once

#include "BoxCollider.h"
#include "GameObject.h"
#include "Sound.h"
#include "Texture.h"
#include "Vector.h"

class Player : public GameObject
{

public:

	Player();
	~Player() override;

	const BoxCollider& GetBound();

	void Update(int deltaTime) override;
	bool Render() override;

private:

	int velocity{ 5 };

	BoxCollider bound;
	Sound footsteps;

	Texture idle;
	Texture walk;

	Vector<int> position;
	Vector<int> directionWalk;
	Vector<int> directionStand;

};