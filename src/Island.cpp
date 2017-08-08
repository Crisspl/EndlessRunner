#include "Island.h"

Island::Island(fhl::Vec2f _pos)
	 : Collideable(Collideable::Coll_Island)
{
	 m_sprite.setTexture(fhl::ResMgr::getTexture("islandTex")->setRepeated(1));

	 std::size_t size = sup::getRand(7, 14);

	 m_sprite.setSize({ size * 32.f, 32.f });
	 m_sprite.setOrigin({ 32.f * size , 0.f })
		  .setPosition(_pos);
	 m_coins = std::vector<Coin>(size);

	 size_t i = 0;
	 for (Coin & c : m_coins)
	 {
		  c.setPosition(m_sprite.getPosition() - m_sprite.getOrigin() + fhl::Vec2f(i++ * 32 + 16, 0));
	 }
}

std::shared_ptr<Collider> Island::getCollider(CollideableObjType _objType)
{
   fhl::Rect * rect = new fhl::Rect(m_sprite.getAABB());

   return std::shared_ptr<Collider>(new BoxCollider(rect));
}

void Island::update(float _dt)
{
	for (Coin & c : m_coins)
		c.update(_dt);
}

void Island::render(const fhl::RenderConf &) const
{
	fhl::Renderer::render(m_sprite);
	for (const Coin & c : m_coins)
		fhl::Renderer::render(c);
}


void Island::move(float _offset)
{
   m_sprite.move({_offset, 0});
   for (Coin & c : m_coins)
	   c.move({ _offset, 0 });
}

std::vector<fhl::Light> Island::getLights() const
{
	fhl::Light light = fhl::Light::point(fhl::Vec3f(), fhl::Color(float(rand() % 100) / 100, float(rand() % 100) / 100, float(rand() % 100) / 100), .5f, 5e-3f, 4e-5f);
	std::vector<fhl::Light> lights(m_coins.size(), light);

	for (int i = 0; i < lights.size(); i++)
		 lights[i].position = fhl::Vec3f(m_coins[i].getPosition(), 300.f);

	return lights;
}
