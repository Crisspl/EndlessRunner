#ifndef ISLAND_H
#define ISLAND_H

#include <vector>
#include <random>

#include <FHL/Graphics/Sprite.h>
#include <FHL/Graphics/Renderable.h>
#include <FHL/Graphics/Renderer.h>
#include <FHL/Graphics/Light.h>
#include <FHL/Graphics/ResMgr.h>
#include <FHL/Maths/vectors.h>

#include "Global.h"
#include "Collideable.h"
#include "Coin.h"

class Island
      : public Collideable,
        public fhl::Renderable
{
public:
   explicit Island(fhl::Vec2f _pos);

public:
   std::shared_ptr<Collider> getCollider(CollideableObjType _objType) override;
   void onCollision(CollideableObjType _objType) override { }

   void update(float _dt);
   void render(const fhl::RenderConf &) const override;
   void move(float _offset);

   fhl::Vec2f getPosition() const { return m_sprite.getPosition(); }
   float getSurfaceHeight() const { return m_sprite.getPosition().y(); }
   std::vector<fhl::Light> getLights() const;
   std::vector<Coin> & getCoins() { return m_coins; }

private:
   fhl::Sprite m_sprite;
   std::vector<Coin> m_coins;
};

#endif // ISLAND_H
