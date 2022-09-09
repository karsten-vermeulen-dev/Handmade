#include "RigidBody.h"

//======================================================================================================
Vector<double> RigidBody::GravityForce(double mass_1, double mass_2, const Vector<double>& distance)
{
	double gravityForce = (gravity * mass_1 * mass_2) /
		distance.Magnitude() * distance.Magnitude();
	return distance.Normalize() * gravityForce;
}
//======================================================================================================
//Vector<double> RigidBody::TorqueForce(const Vector<double>& force,
//	const Vector<double>& contactPosition, const Vector<double>& centreOfMass)
//{
//	//The result produces a vector, used for the rotation axis and torque magnitude
//	return glm::cross(force, (centreOfMass - contactPosition));
//}
//======================================================================================================
RigidBody::RigidBody() {}
//======================================================================================================
double RigidBody::GetAngle() const
{
	return angle;
}
//======================================================================================================
double RigidBody::GetAngularVelocity() const
{
	return angularVelocity;
}
//======================================================================================================
const Vector<double>& RigidBody::GetForce() const
{
	return force;
}
//======================================================================================================
//const Vector<double>& RigidBody::GetTorque() const
//{
//	return torque;
//}
//======================================================================================================
const Vector<double>& RigidBody::GetPosition() const
{
	return position;
}
//======================================================================================================
const Vector<double>& RigidBody::GetVelocity() const
{
	return velocity;
}
//======================================================================================================
void RigidBody::SetMass(double mass)
{
	this->mass = mass;
}
//======================================================================================================
void RigidBody::SetAngle(double angle)
{
	this->angle = angle;
}
//======================================================================================================
void RigidBody::SetAngularMass(double mass)
{
	angularMass = mass;
}
//======================================================================================================
void RigidBody::SetAngularVelocity(double velocity)
{
	angularVelocity = velocity;
}
//======================================================================================================
void RigidBody::SetForce(const Vector<double>& force)
{
	this->force = force;
}
//======================================================================================================
void RigidBody::SetTorque(const Vector<double>& torque)
{
	//this->torque = torque;
}
//======================================================================================================
void RigidBody::SetPosition(const Vector<double>& position)
{
	this->position = position;
}
//======================================================================================================
void RigidBody::SetVelocity(const Vector<double>& velocity)
{
	this->velocity = velocity;
}
//======================================================================================================
void RigidBody::AddForce(const Vector<double>& force)
{
	this->force += force;
}
//======================================================================================================
void RigidBody::AddTorque(const Vector<double>& force, const Vector<double>& contactPoint)
{
	AddForce(force);

	//T = F x d
	//TODO - Fix this
	Vector<double> distance = contactPoint - position;
	//Vector<double> torque = glm::cross(force, distance);
	//torque += torque;
}
//======================================================================================================
void RigidBody::Update(float deltaTime)
{
	if (mass > 0.0) acceleration = (force / static_cast<float>(mass));
	//if (angularMass > 0.0) angularAcceleration = glm::length(torque) / angularMass;

	Vector<double> oldVelocity = velocity;
	velocity += acceleration * deltaTime;
	position += (velocity + oldVelocity) * 0.5f * deltaTime;

	double oldAngularVelocity = angularVelocity;
	angularVelocity += angularAcceleration * deltaTime;
	angle += (angularVelocity + oldAngularVelocity) * 0.5 * deltaTime;

	//Extra code to be sorted later (WIP)
	//Here we assume AngVel is a Vec3 object
	//angularAcceleration = torque;
	/*if (angVel.SqLen() > 0)
	{
		Vec3f axis = angVel;
		axis.Normalise();
		Quaternion rotThisFrame(axis, angVel.Len() * dt);
		quat = rotThisFrame * quat;
	}*/
}