#ifndef CIRCLECOLLIDER_H
#define CIRCLECOLLIDER_H

#include <FHL/Utility/Circle.h>

#include "Collider.h"

class RectsCollider;
class BoxCollider;

class CircleCollider
	:public Collider
{
public:
	CircleCollider(const fhl::Vec2f & _center, float _radius) : Collider(Collider::Circle), m_circle{_center, _radius} {}

public:
	virtual bool isCollision(const CircleCollider & _collider) const override;
	virtual bool isCollision(const BoxCollider & _collider) const override;

	bool contains(const fhl::Vec2f & _p) const;

	fhl::Vec2f getCenter() const { return m_circle.getCenter(); }
	float getRadius() const { return m_circle.getRadius(); }

private:
	fhl::Circle m_circle;
};

#endif
