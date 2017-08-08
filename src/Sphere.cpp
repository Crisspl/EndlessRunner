#include "Sphere.h"

#define REGISTER_SPHERE_STATES(stateName) \
   m_onEnter[State_##stateName] \
     = &Sphere::stateName##_onEnter; \
   m_onExit[State_##stateName] \
     = &Sphere::stateName##_onExit; \
   m_update[State_##stateName] \
     = &Sphere::stateName##_update;

Sphere::Sphere(Hero * _owner) :
	m_sprite(fhl::ResMgr::loadTexture("sphereTex", "Resources/Tex/bullet2.png")),
	m_animMgr(&m_sprite, 0.08f, s_frameSize, 8),
	m_startVelociy(30.f),
	m_velocity(m_startVelociy),
	m_owner(_owner),
	m_currentState(StateCount)
{
	REGISTER_SPHERE_STATES(Idle)
	REGISTER_SPHERE_STATES(Thrown)
	REGISTER_SPHERE_STATES(Return)
#undef REGISTER_SPHERE_STATES

	m_sprite.setSize(s_frameSize);
	m_sprite.setOrigin(m_sprite.getSize() / 2.f);

	changeState(State_Idle);
}

std::shared_ptr<Collider> Sphere::getCollider(CollideableObjType _objType)
{
	return std::shared_ptr<Collider>(new CircleCollider(m_sprite.getPosition(), m_sprite.getSize().x() / 2.f));
}

void Sphere::render(const fhl::RenderConf &) const
{
	fhl::Renderer::render(m_sprite);
}

void Sphere::update(float dt)
{
	m_animMgr.update(dt);
	(this->*m_update[m_currentState])(dt);
}

void Sphere::changeState(const State _newState)
{
	if (m_currentState < StateCount &&
		m_currentState != _newState)
	{
		(this->*m_onExit[m_currentState])(_newState);
	}

	const State prevState(m_currentState);

	m_currentState = _newState;

	(this->*m_onEnter[m_currentState])(prevState);
}

/* State Idle Methods */

void Sphere::Idle_onEnter(const Sphere::State _prevState)
{
	m_sprite.setPosition(m_owner->getBulletIdlePos());
	m_velocity = 0;
}

void Sphere::Idle_onExit(const Sphere::State _newState)
{}

void Sphere::Idle_update(float dt)
{
	m_sprite.setPosition(m_owner->getBulletIdlePos());
}

/* State Thrown Methods */

void Sphere::Thrown_onEnter(const Sphere::State _prevState)
{
	m_velocity = m_startVelociy;
}

void Sphere::Thrown_onExit(const Sphere::State _newState)
{
	m_direction = fhl::Vec2f();
}

void Sphere::Thrown_update(float dt)
{
	m_velocity -= m_startVelociy * dt;
	if (m_velocity < 0)
	{
		changeState(State_Return);
		return;
	}
	fhl::Vec2f moveOffset = m_direction * m_velocity;
	m_sprite.move(moveOffset);
}

/* State Return Methods */

void Sphere::Return_onEnter(const Sphere::State _prevState)
{}

void Sphere::Return_onExit(const Sphere::State _newState)
{}

void Sphere::Return_update(float dt)
{
	m_velocity -= m_startVelociy * dt;

	fhl::Vec2f myPos = m_sprite.getPosition();
	fhl::Vec2f ownerPos = m_owner->getBulletIdlePos();

	fhl::Vec2f dir = (myPos - ownerPos).normalized();

	fhl::Vec2f moveOffset = dir * m_velocity;
	m_sprite.move(moveOffset);
}
