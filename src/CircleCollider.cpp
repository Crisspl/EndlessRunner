#include "CircleCollider.h"

#include "BoxCollider.h"

bool CircleCollider::isCollision(const CircleCollider & _collider) const
{
	return m_circle.overlaps(_collider.m_circle);
}

bool CircleCollider::isCollision(const BoxCollider& _collider) const
{
	return m_circle.overlaps(_collider.getRect());
}

bool CircleCollider::contains(const fhl::Vec2f & _p) const
{
	return m_circle.contains(_p);
}
