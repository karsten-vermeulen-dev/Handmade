#include "Plane.h"

//======================================================================================================
void Plane::SetPoint1(int x, int y)
{
	planePoints.point1.x = x;
	planePoints.point1.y = y;
}
//======================================================================================================
void Plane::SetPoint2(int x, int y)
{
	planePoints.point2.x = x;
	planePoints.point2.y = y;
}
//======================================================================================================
void Plane::Update()
{
	auto plane = planePoints.point2 - planePoints.point1;

	normal.x = -plane.y;
	normal.y = plane.x;

	if (normal.x == -0)
	{
		normal.x = 0;
	}

	normal = normal.Normalize();
	distanceFromOrigin = (int)(normal.Dot(planePoints.point1));
}
//======================================================================================================
Plane::PlaneSide Plane::SideOfPlane(int x, int y) const
{
	auto distanceFromPlane = DistanceFromPlane(x, y);

	if (distanceFromPlane < 0)
	{
		return PlaneSide::Negative;
	}

	if (distanceFromPlane > 0)
	{
		return PlaneSide::Positive;
	}

	return PlaneSide::OnPlane;
}
//======================================================================================================
int Plane::DistanceFromPlane(int x, int y) const
{
	return (normal.Dot(Vector<int>(x, y))) - distanceFromOrigin;
}
//======================================================================================================
bool Plane::IsColliding(const SphereCollider& secondSphere) const
{
	auto position = secondSphere.GetPosition();
	return (abs(DistanceFromPlane(position.x, position.y)) <= secondSphere.GetRadius());
}