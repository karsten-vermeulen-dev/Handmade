#pragma once
#include "SphereCollider.h"
#include "Vector.h"

struct PlanePoints
{
	Vector<int> point1{ 0, 0 };
	Vector<int> point2{ 0, 0 };
};

class Plane
{

public:

	enum class PlaneSide
	{
		OnPlane,
		Positive,
		Negative
	};

	Plane() {}

	void SetPoint1(int x, int y);
	void SetPoint2(int x, int y);
	void SetPosition(int x, int y);

	PlaneSide SideOfPlane(int x, int y) const;
	int DistanceFromPlane(int x, int y) const;
	bool IsColliding(const SphereCollider& secondSphere) const;

	void Update();

private:

	PlanePoints planePoints;
	int distanceFromOrigin{ 0 };

	Vector<int> normal{ 0, 0 };
	Vector<int> position{ 0, 0 };

};