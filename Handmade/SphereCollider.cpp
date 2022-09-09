#include "SphereCollider.h"

//======================================================================================================
int SphereCollider::GetRadius() const
{
	return radius;
}
//======================================================================================================
const Vector<int>& SphereCollider::GetPosition() const
{
	return position;
}
//======================================================================================================
void SphereCollider::SetRadius(int radius)
{
	this->radius = radius;
}
//======================================================================================================
void SphereCollider::SetPosition(int x, int y)
{
	position.x = x;
	position.y = y;
}
//======================================================================================================
bool SphereCollider::IsColliding(const SphereCollider& secondSphere) const
{
	Vector<int> centerPoint_1(position.x + radius, position.y + radius);
	Vector<int> centerPoint_2(secondSphere.position.x + secondSphere.radius,
		secondSphere.position.y + secondSphere.radius);

	return (centerPoint_1.Distance(centerPoint_2) <= (radius + secondSphere.radius));
}