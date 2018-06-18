#pragma once

#include "physics/PhysicsStaticObject.h"

class Mikyna
{
public:
	Mikyna();
	~Mikyna();
	void Draw();
private:
	SkinModel m_model;
	PhysicsStaticObject m_phyStaticObject;
};

