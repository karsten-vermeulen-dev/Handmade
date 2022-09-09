#pragma once
#include "Vector.h"

class SphereCollider
{

public:

	SphereCollider() {}

	int GetRadius() const;
	const Vector<int>& GetPosition() const;

	void SetRadius(int radius);
	void SetPosition(int x, int y);

	bool IsColliding(const SphereCollider& secondSphere) const;

private:

	int radius{ 0 };
	Vector<int> position;

};