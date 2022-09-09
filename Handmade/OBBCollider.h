#pragma once
#include <array>
#include "BoxCollider.h"
#include "Vector.h"

class OBBCollider
{

public:

	OBBCollider() {}

	void SetRotation(float angle);
	void SetScale(float x, float y);
	void SetPosition(float x, float y);
	void SetDimension(float width, float height);

	bool IsColliding(const OBBCollider& secondBox) const;
	bool IsColliding(const BoxCollider& secondBox) const;

	void Update();

private:

	bool IsColliding(const OBBCollider* tempBox) const;

	float angle{ 0.0f };

	Vector<float> scale{ 1.0f, 1.0f };
	Vector<float> position{ 0.0f, 0.0f };
	Vector<float> dimension{ 1.0f, 1.0f };

	Vector<float> upAxis{ Vector<float>::Up };
	Vector<float> rightAxis{ Vector<float>::Right };
	std::array<Vector<float>, 4> corners{ Vector<float>::Zero };

};