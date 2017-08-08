#ifndef COLLIDEABLE_H
#define COLLIDEABLE_H

#include <utility>
#include <memory>
#include <iostream>

#include "Collider.h"
#include "CircleCollider.h"
#include "BoxCollider.h"

class Collideable
{
public:

   enum CollideableObjType
   {
      Coll_Hero,
      Coll_Island,
      Coll_Coin,
      Coll_Any
   };

protected:
   explicit Collideable(CollideableObjType _objType = Coll_Any)
               : m_objType(_objType) {}

public:
   virtual ~Collideable(){}

public:
   CollideableObjType getObjType() { return m_objType; }
   virtual bool isCollision(Collideable& _colliding);

   virtual std::shared_ptr<Collider> getCollider(CollideableObjType _objType) = 0;
   virtual void onCollision(CollideableObjType _objType) = 0;

private:
   CollideableObjType m_objType;
};

#endif // COLLIDEABLE_H
