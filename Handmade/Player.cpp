#include "Input.h"
#include "Player.h"

//======================================================================================================
Player::Player()
{
	idle.Load("Characters/Adventure_boy_idle.png", "Idle");
	idle.SetTexture("Idle");
	idle.SetDimension(200, 200);
	idle.SetSourceDimension(10, 1, 5880, 600);
	idle.IsAnimated(true);
	idle.IsAnimationLooping(true);
	idle.SetAnimationVelocity(20.0f);

	walk.Load("Characters/Adventure_boy_run.png", "Walk");
	walk.SetTexture("Walk");
	walk.SetDimension(200, 200);
	walk.SetSourceDimension(10, 1, 5880, 600);
	walk.IsAnimated(true);
	walk.IsAnimationLooping(true);
	walk.SetAnimationVelocity(20.0f);

	footsteps.Load("Melee.wav", "Foot");
	footsteps.SetSound("Foot");

	SetPosition(600, 500);
	bound.SetDimension(125, 250);
}
//======================================================================================================
const BoxCollider& Player::GetBound()
{
	return bound;
}
//======================================================================================================
void Player::Update(int deltaTime)
{
	auto keys = Input::Instance()->GetKey();

	//Check if left or right key is pressed and set player's direction accordingly
	//assign standing direction as well so that when no key is pressed the correct
	//direction is set for the standing stance and sprite of the player object
	if (Input::Instance()->IsKeyPressed(HM_KEY_LEFT))
	{
		directionStand = directionWalk = Vector<int>::Left;
	}

	else if (Input::Instance()->IsKeyPressed(HM_KEY_RIGHT))
	{
		directionStand = directionWalk = Vector<int>::Right;
	}

	else
	{
		directionWalk = Vector<int>::Zero;
	}

	position += directionWalk * velocity;
	bound.SetPosition(position.x, position.y);

	idle.Update(deltaTime);
	walk.Update(deltaTime);
}
//======================================================================================================
bool Player::Render()
{
	//Flag to be used for playing "footstep" sound effect
	//We don't want it to play multiple times at once!
	static bool isWalking = false;

	//Check if player is walking or not and render the correct walking cycle
	//render the correct standing stance sprite based on which way he is facing
	if (directionWalk.x == 0 && directionWalk.y == 0)
	{
		directionStand.x < 0.0f ? idle.Render(position.x, position.y, 0.0, Texture::Flip::Horizontal)
			: idle.Render(position.x, position.y);
		isWalking = false;
	}

	else
	{
		directionWalk.x < 0.0f ? walk.Render(position.x, position.y, 0.0, Texture::Flip::Horizontal)
			: walk.Render(position.x, position.y);

		if (!isWalking)
		{
			footsteps.Play();
			isWalking = true;
		}
	}

	return true;
}
//======================================================================================================
Player::~Player()
{
	footsteps.Unload("Foot");
	walk.Unload("Walk");
	idle.Unload("Idle");
}