#ifndef HERO_H
#define HERO_H

#include <FHL/Graphics/Sprite.h>
#include <FHL/Graphics/Renderer.h>
#include <FHL/Graphics/Transformable.h>
#include <FHL/Graphics/Renderable.h>
#include <FHL/Maths/Vec2.h>

#include "Collideable.h"
#include "Global.h"
#include "AnimationMgr.h"

#define DECLARE_HERO_STATE_METHODS(stateName) \
	void stateName##_onEnter(const Hero::State); \
	void stateName##_onExit(const Hero::State); \
	void stateName##_update(float);

class Hero : 
	public Collideable,
	public fhl::Renderable
{
public:
	enum State
	{
		State_Move = 0,
		State_Jump,
		State_Fall,

		StateCount
	};

public:
	Hero();
	~Hero() {}

	std::shared_ptr<Collider> getCollider(CollideableObjType _objType) override;
	void onCollision(CollideableObjType _objType) override { }

	void render(const fhl::RenderConf &) const override;
	void update(float dt);
	void changeState(const State _newState);

	fhl::Vec2f getPosition() const { return m_heroSprite.getPosition(); }
	fhl::Vec2f getBulletIdlePos() const { return getPosition() - m_heroSprite.getOrigin() + fhl::Vec2f(m_heroSprite.getSize().x(), m_heroSprite.getSize().y() / 2.f); }
	State getState() const { return m_currentState; }

	void setPosition(fhl::Vec2f _pos) { m_heroSprite.setPosition(_pos); }
	void setPosY(float _y) { m_heroSprite.setPosition({ getPosition().x(), _y }); }

private:
	void move(fhl::Vec2f _offset);

	DECLARE_HERO_STATE_METHODS(Move)
	DECLARE_HERO_STATE_METHODS(Jump)
	DECLARE_HERO_STATE_METHODS(Fall)
#undef DECLARE_HERO_STATE_METHODS

	void (Hero:: *m_onEnter[StateCount])
		(const Hero::State prevState);
	void (Hero:: *m_onExit[StateCount])
		(const Hero::State nextState);
	void (Hero:: *m_update[StateCount])(float);


private:
	State m_currentState;
	fhl::Sprite m_heroSprite;
	AnimationMgr m_animMgr;
	fhl::Vec2f m_velocity;

	constexpr static const float JUMP_VEL = -700.f;
	constexpr static const fhl::Vec2u FRAME_SIZE{ 78u, 93u };
	constexpr static std::size_t FRAMES_PER_STATE[StateCount]{ 6, 1, 1 };
};

#endif // HERO_H
