#ifndef COIN_H
#define COIN_H

#include <FHL/Graphics/Renderer.h>
#include <FHL/Graphics/Renderable.h>
#include <FHL/Graphics/Transformable.h>
#include <FHL/Graphics/Sprite.h>
#include <FHL/Graphics/ResMgr.h>

#include "Collideable.h"
#include "CircleCollider.h"
#include "Global.h"
#include "SoundMgr.h"

class Coin
	: public fhl::Renderable,
	  public fhl::Transformable,
	  public Collideable
{
public:
	Coin();

	void update(float _dt);
	void render(const fhl::RenderConf &) const override;
	std::shared_ptr<Collider> getCollider(Collideable::CollideableObjType) override;
	void onCollision(Collideable::CollideableObjType) override;

private:
	fhl::Sprite m_sprite;
	float m_elapsedTime;
	size_t m_currCell;
};

#endif // COIN_H