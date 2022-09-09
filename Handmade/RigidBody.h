#pragma once
#include "Vector.h"

const double gravity = 1.0000000000667;

class RigidBody
{

public:

	static Vector<double> GravityForce(double mass_1,
		double mass_2, const Vector<double>& distance);

	//TODO - Fix this for 2D version
	/*static Vector<double> TorqueForce(const Vector<double>& force,
		const Vector<double>& contactPosition, const Vector<double>& centreOfMass);*/

	RigidBody();

	double GetAngle() const;
	double GetAngularVelocity() const;

	const Vector<double>& GetForce() const;
	//const Vector<double>& GetTorque() const;
	const Vector<double>& GetPosition() const;
	const Vector<double>& GetVelocity() const;

	void SetMass(double mass);
	void SetAngle(double angle);
	void SetAngularMass(double mass);
	void SetAngularVelocity(double velocity);

	void SetForce(const Vector<double>& force);
	void SetTorque(const Vector<double>& torque);
	void SetPosition(const Vector<double>& position);
	void SetVelocity(const Vector<double>& velocity);

	void AddForce(const Vector<double>& force);
	void AddTorque(const Vector<double>& force, const Vector<double>& contactPoint);

	void Update(float deltaTime);

private:

	double mass{ 0.0 };
	double angle{ 0.0 };
	double angularMass{ 0.0 };
	double angularVelocity{ 0.0 };
	double angularAcceleration{ 0.0 };

	Vector<double> force{ 0.0, 0.0 };
	//Vector<double> m_torque{ 0.0, 0.0 };
	Vector<double> position{ 0.0, 0.0 };
	Vector<double> velocity{ 0.0, 0.0 };
	Vector<double> acceleration{ 0.0, 0.0 };

};