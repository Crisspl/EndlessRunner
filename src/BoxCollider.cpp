#include "BoxCollider.h"

#include "CircleCollider.h"

BoxCollider::BoxCollider(fhl::Rect * _rect) :
	Collider(Collider::Box),
	m_rect(_rect)
{
}

bool BoxCollider::isCollision(const CircleCollider & _collider) const
{
	return _collider.isCollision(*this);
}

bool BoxCollider::isCollision(const BoxCollider & _collider) const
{
   return m_rect->overlaps(_collider.getRect());
}
