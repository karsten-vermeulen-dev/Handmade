#include <algorithm>
#include "BoxCollider.h"

//======================================================================================================
BoxCollider BoxCollider::GetCollisionRegion(const BoxCollider& secondBox)
{
	BoxCollider collider;

	collider.min.x = std::max(min.x, secondBox.min.x);
	collider.min.y = std::max(min.y, secondBox.min.y);
	collider.max.x = std::min(max.x, secondBox.max.x);
	collider.max.y = std::max(max.y, secondBox.max.y);

	return collider;
}
//======================================================================================================
void BoxCollider::SetPosition(int x, int y)
{
	position.x = x;
	position.y = y;
}
//======================================================================================================
void BoxCollider::SetDimension(int width, int height)
{
	dimension.x = width;
	dimension.y = height;
}
//======================================================================================================
void BoxCollider::Update()
{
	min.x = position.x;
	min.y = position.y;
	max.x = position.x + dimension.x;
	max.y = position.y + dimension.y;
}
//======================================================================================================
bool BoxCollider::IsColliding(const BoxCollider& secondBox) const
{
	return ((max.x > secondBox.min.x && secondBox.max.x > min.x) &&
		(max.y > secondBox.min.y && secondBox.max.y > min.y));
}
//======================================================================================================
bool BoxCollider::IsColliding(const BoxCollider& secondBox,
	const Vector<int>& lhsBoxVelocity,
	const Vector<int>& rhsBoxVelocity,
	float maxTime, float* firstTime)
{
	//Velocity of box 1 relative to box 2
	Vector<int> relativeVelocity = lhsBoxVelocity - rhsBoxVelocity;

	//Time of first contact in X
	auto x0 = 0.0f;

	if (secondBox.min.x > max.x && relativeVelocity.x > 0)
	{
		x0 = (secondBox.min.x - max.x) / static_cast<float>(relativeVelocity.x);
	}

	else if (min.x > secondBox.max.x && relativeVelocity.x < 0)
	{
		//Swap to get +ve time
		x0 = (secondBox.max.x - min.x) / static_cast<float>(relativeVelocity.x);
	}

	//Time of final contact in X
	auto x1 = maxTime;

	if (secondBox.max.x > min.x && relativeVelocity.x > 0)
	{
		x1 = (secondBox.max.x - min.x) / static_cast<float>(relativeVelocity.x);
	}

	else if (max.x > secondBox.min.x && relativeVelocity.x < 0)
	{
		//Swap to get +ve time
		x1 = (secondBox.min.x - max.x) / static_cast<float>(relativeVelocity.x);
	}

	//Time of first contact in Y
	auto y0 = 0.0f;

	if (secondBox.min.y > max.y && relativeVelocity.y > 0)
	{
		y0 = (secondBox.min.y - max.y) / static_cast<float>(relativeVelocity.y);
	}

	else if (min.y > secondBox.max.y && relativeVelocity.y < 0)
	{
		//Swap to get +ve time
		y0 = (secondBox.max.y - min.y) / static_cast<float>(relativeVelocity.y);
	}

	//Time of final contact in Y
	auto y1 = maxTime;

	if (secondBox.max.y > min.y && relativeVelocity.y > 0)
	{
		y1 = (secondBox.max.y - min.y) / static_cast<float>(relativeVelocity.y);
	}

	else if (max.y > secondBox.min.y && relativeVelocity.y < 0)
	{
		//Swap to get +ve time
		y1 = (secondBox.min.y - max.y) / static_cast<float>(relativeVelocity.y);
	}

	//Time of first contact for the 2 rects is the MAX
	//of the times of first contact in X and Y
	auto first = std::max(x0, y0);

	//Time of last contact for the 2 rects is the MIN
	//of the times of last contact in X and Y
	auto last = std::min(x1, y1);

	//If the time of final contact is AFTER the time of
	//first contact, then the rects do intersect
	auto intersect = (last > first && first < maxTime);

	//Pass back time of first contact
	if (firstTime)
	{
		*firstTime = first;
	}

	return intersect;
}