#include "Hero.h"

#include <FHL/Graphics/ResMgr.h>

#define REGISTER_HERO_STATES(stateName) \
   m_onEnter[State_##stateName] \
     = &Hero::stateName##_onEnter; \
   m_onExit[State_##stateName] \
     = &Hero::stateName##_onExit; \
   m_update[State_##stateName] \
     = &Hero::stateName##_update;

Hero::Hero() :
	Collideable(Collideable::Coll_Hero),
	m_currentState(StateCount),
	m_heroSprite(fhl::ResMgr::loadTexture("heroTex", "Resources/Tex/runner_sprites.png")),
	m_animMgr(&m_heroSprite, 0.08f, FRAME_SIZE, 6, 1, 1)
{
	REGISTER_HERO_STATES(Move)
	REGISTER_HERO_STATES(Jump)
	REGISTER_HERO_STATES(Fall)
#undef REGISTER_HERO_STATES

	m_heroSprite.setSize(FRAME_SIZE);
	m_heroSprite.setOrigin(m_heroSprite.getSize() * fhl::Vec2f(0.5f, 1));
	m_heroSprite.setColor(fhl::Color::Magenta);

	changeState(State_Move);
	m_animMgr.setColumnwise(true);
}

std::shared_ptr<Collider> Hero::getCollider(CollideableObjType _objType)
{
	fhl::Rect *rect = new fhl::OrientedRect(m_heroSprite.getOBB());
	//fhl::Rect *rect = new fhl::OrientedRect(m_heroSprite.getSize(), m_heroSprite.getTransformData());
	//fhl::Rect *rect = new fhl::OrientedRect(m_heroSprite.getTransformData().botLeft, m_heroSprite.getSize(), m_heroSprite.getOrigin(), m_heroSprite.getRotation());

	rect->adjustY(-m_heroSprite.getSize().y() * 0.8f)
		.translate({ 0, m_heroSprite.getSize().y() * 0.8f });

	return std::shared_ptr<Collider>(new BoxCollider(rect));
}

void Hero::render(const fhl::RenderConf &) const
{
	fhl::Renderer::render(m_heroSprite);
}

void Hero::update(float dt)
{
	m_animMgr.update(dt);
	(this->*m_update[m_currentState])(dt);
}

void Hero::changeState(const Hero::State _newState)
{
	if (m_currentState < StateCount &&
		m_currentState != _newState)
	{
		(this->*m_onExit[m_currentState])(_newState);
	}

	const Hero::State prevState(m_currentState);

	m_currentState = _newState;
	m_animMgr.setState(_newState);

	(this->*m_onEnter[m_currentState])(prevState);
}

void Hero::move(fhl::Vec2f _offset)
{
	m_heroSprite.move(_offset);
}

//////////// MOVE STATE ////////////////////

void Hero::Move_onEnter(Hero::State prevState)
{
	m_velocity = fhl::Vec2f();
}

void Hero::Move_onExit(Hero::State nextState){}

void Hero::Move_update(float dt){}

//////////// JUMP STATE ////////////////////

void Hero::Jump_onEnter(Hero::State prevState)
{
	m_velocity.y() = JUMP_VEL;
}

void Hero::Jump_onExit(Hero::State nextState)
{
}

void Hero::Jump_update(float dt)
{
	move(m_velocity * dt);
	m_velocity.y() += dt * sup::GRAVITY;
	if (m_velocity.y() > 0)
		changeState(State_Fall);
}

//////////// FALL STATE ////////////////////

void Hero::Fall_onEnter(Hero::State prevState)
{
}

void Hero::Fall_onExit(Hero::State nextState)
{
}

void Hero::Fall_update(float dt)
{
	move(m_velocity * dt);
	m_velocity.y() += dt * sup::GRAVITY;
}
