#include "Game.h"

int main(int argc, char *argv[])
{
   srand(time(0));

   Game::initSystems();

   Game::get().run();

   fhl::ResMgr::clear();

   return 0;
}
