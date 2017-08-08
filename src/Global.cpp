#include "Global.h"

namespace sup
{
   const float GRAVITY = 1900.f;

   unsigned getRand(unsigned a, unsigned b)
   {
      return (rand()%((b + 1)- a)) + a;
   }
}
