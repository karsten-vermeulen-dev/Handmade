#pragma once
#include "Vector.h"

class BoxCollider
{

public:

	BoxCollider GetCollisionRegion(const BoxCollider& secondBox);

	void SetPosition(int x, int y);
	void SetDimension(int width, int height);

	void Update();
	bool IsColliding(const BoxCollider& secondBox) const;

	bool IsColliding(
		const BoxCollider& secondBox,
		const Vector<int>& lhsBoxVelocity, // velocity of rectangle 1
		const Vector<int>& rhsBoxVelocity, // velocity of rectangle 2
		float maxTime, // max time - i.e. your DT for this frame
		float* firstTime = 0); // Set to time of first contact 

private:

	Vector<int> min;
	Vector<int> max;
	Vector<int> position;
	Vector<int> dimension{ 1, 1 };

};