#ifndef COLLIDER_H
#define COLLIDER_H

class CircleCollider;
class BoxCollider;

class Collider
{
public:
	enum Type
	{
		Circle,
		Box,

		CountColliderTypes
	};

protected:
	Collider(Type _type) : type(_type) {}

public:
	virtual ~Collider() {}

public:
	virtual bool isCollision(const CircleCollider& _collider) const = 0;
	virtual bool isCollision(const BoxCollider& _collider) const = 0;

	Type type;
};

#endif // COLLIDER_H

