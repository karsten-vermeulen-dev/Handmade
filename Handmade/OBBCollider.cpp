#include "OBBCollider.h"
#include "Screen.h"

//======================================================================================================
void OBBCollider::SetRotation(float angle)
{
	angle = angle;
}
//======================================================================================================
void OBBCollider::SetScale(float x, float y)
{
	scale.x = x;
	scale.y = y;
}
//======================================================================================================
void OBBCollider::SetPosition(float x, float y)
{
	position.x = x;
	position.y = y;
}
//======================================================================================================
void OBBCollider::SetDimension(float width, float height)
{
	dimension.x = width;
	dimension.y = height;
}
//======================================================================================================
bool OBBCollider::IsColliding(const OBBCollider& secondBox) const
{
	OBBCollider tempBox[2];
	tempBox[0] = *this;
	tempBox[1] = secondBox;

	return IsColliding(tempBox);
}
//======================================================================================================
bool OBBCollider::IsColliding(const BoxCollider& secondBox) const
{
	//TODO - Fix this
	/*OBBCollider collider;

	collider.SetScale(secondBox.GetScale());
	collider.SetPosition(secondBox.GetPosition());
	collider.SetDimension(secondBox.GetDimension());
	collider.Update();

	return IsColliding(collider);*/
	return true;
}
//======================================================================================================
void OBBCollider::Update()
{
	Vector<float> halfDimension(dimension.x * scale.x * 0.5f, dimension.y * scale.y * 0.5f);

	//Use the up and right vector to calculate box's corners 
	//below and to create projection vectors to project onto later on
	//We have to reset them to their defaults before rotating them
	upAxis = Vector<float>::Up;
	rightAxis = Vector<float>::Right;

	//TODO - Fix this. We need to rotate the up/right vectors around Z
	//TODO - Do we use a simple 2x2 matrix here or find some way to rotate vector?

	//Transform the up and right vectors based on how the OBBCollider is rotated 
	/*upAxis = rotation.GetMatrix() * upAxis * halfDimension.y;
	rightAxis = rotation.GetMatrix() * rightAxis * halfDimension.x;*/

	//Calculate all four corners of the box based on bound's centre 
	//position, starting in the top left corner and moving clockwise
	corners[0] = position - rightAxis + upAxis;
	corners[1] = position + rightAxis + upAxis;
	corners[2] = position + rightAxis - upAxis;
	corners[3] = position - rightAxis - upAxis;
}
//======================================================================================================
bool OBBCollider::IsColliding(const OBBCollider* tempBox) const
{
	//Assign all four temporary axes based on both boxes' up and right axes 
	//These will be the four axes that all eight corners are projected onto
	std::array<Vector<float>, 4> axes;

	axes[0] = tempBox[0].rightAxis;
	axes[1] = tempBox[0].upAxis;
	axes[2] = tempBox[1].rightAxis;
	axes[3] = tempBox[1].upAxis;

	for (int i = 0; i < 4; i++)
	{
		//Reset the min and max extent values each time a new axis is tested
		//Set both min and max to the first projected corner of each box
		std::array<Vector<float>, 2> extents;
		extents[0].x = extents[0].y = corners[0].Dot(axes[i].Normalize());
		extents[1].x = extents[1].y = tempBox[1].corners[0].Dot(axes[i].Normalize());

		//Now loop through each box...
		for (int j = 0; j < 2; j++)
		{
			//...and through each corner
			for (int k = 0; k < 4; k++)
			{
				//project each box's corner onto the current active axis
				//use the length of this projection to calculate min and max projection values 
				auto projection = tempBox[j].corners[k].Dot(axes[i].Normalize());

				//Find the min and max extent values for each box
				extents[j].x = std::min(projection, extents[j].x);
				extents[j].y = std::max(projection, extents[j].y);
			}
		}

		//If there is at least 1 extent non-overlap found
		//boxes do not collide, so return false immediately
		if (!(extents[0].y > extents[1].x && extents[1].y > extents[0].x))
		{
			return false;
		}
	}

	//Otherwise there are extent overlaps for each axis
	//and that means both boxes collide, so return true
	return true;
}