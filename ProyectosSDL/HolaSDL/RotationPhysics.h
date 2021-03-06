#pragma once
#include "PhysicsComponent.h"
class RotationPhysics :
	public PhysicsComponent
{
private:
	double angle_;
public:
	RotationPhysics(double angle);
	~RotationPhysics();
	virtual void update(GameObject* o, Uint32 time);
};

