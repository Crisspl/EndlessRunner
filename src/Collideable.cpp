#include "Collideable.h"

bool Collideable::isCollision(Collideable& _colliding)
{
   std::shared_ptr<Collider> myColliderPtr( this->getCollider(_colliding.getObjType()) );
   std::shared_ptr<Collider> outerCollider( _colliding.getCollider(this->getObjType()) );

   bool collided(0);

#define _TRY(type) (type* convertedCollider = dynamic_cast<type*>(outerCollider.get())) \
		 { \
			collided = myColliderPtr->isCollision(*convertedCollider); \
		 }

   if _TRY(CircleCollider)
   else if _TRY(BoxCollider)

#undef _TRY

   if(collided)
   {
	  _colliding.onCollision(this->getObjType());
	  this->onCollision(_colliding.getObjType());
   }

   return collided;
}
