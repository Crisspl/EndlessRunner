#include "Game.h"

#include <FHL/Graphics/Configurator.h>
#include <FHL/Maths/vectors.h>
#include <FHL/Utility/Debug.h>

#include "Input.h"

SDL_Window* Game::m_window;
SDL_GLContext Game::m_context;

Game::Game() : 
	m_sphere(&m_hero),
	m_running(true),
	m_rt(fhl::ResMgr::createTexture("rt", { 200, 200 })),
	m_spr(m_rt.getTexture())
{
	m_spr.setRotation(270.f).setPosition({ 400, 300 }).setOrigin(m_spr.getSize() / 2.f);

   fhl::ResMgr::loadTexture("islandTex", "Resources/Tex/tile.png");
   fhl::ResMgr::loadTexture("coinTex", "Resources/Tex/coin.png");
   SoundMgr::loadSound("Resources/Sounds/coin_gather_sound.wav", "coinGatherSound");
   SoundMgr::getSound("coinGatherSound").setVolume(25);

   m_bgMusic.openFromFile("Resources/Sounds/through_the_fire_n_flames.wav");
   m_bgMusic.setLoop(true);
   m_bgMusic.setVolume(10.f);

   m_hero.setPosition({200.f, (float)WIN_Y});
}

Game& Game::get()
{
   static Game instance;
   return instance;
}

void Game::run()
{
   mainLoop();
}

void Game::initSystems()
{
   SDL_Init(SDL_INIT_EVERYTHING);

   m_window = SDL_CreateWindow(
                 "EndlessRunner",
                 SDL_WINDOWPOS_UNDEFINED,
                 SDL_WINDOWPOS_UNDEFINED,
                 WIN_X,
                 WIN_Y,
                 SDL_WINDOW_OPENGL
             );
   m_context = SDL_GL_CreateContext(m_window);

   SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
   SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
   SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
   SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);

   SDL_GL_SetSwapInterval(1);

   fhl::Configurator::init(WIN_X, WIN_Y);
}

void Game::mainLoop()
{
	m_bgMusic.play();
	while (m_running)
	{
		dt = 1.f / 60.f;

		handleEvents();
		update();
		draw();
	}
	SDL_Quit();
}

void Game::handleEvents()
{
   SDL_Event event;

   while (SDL_PollEvent(&event)) {
       switch (event.type) {
           case SDL_QUIT:
               m_running = false;
               break;
           case SDL_KEYDOWN:
               /*if(event.key.keysym.sym == SDLK_SPACE)
                  m_hero.changeState(Hero::State_Jump);
               if(event.key.keysym.sym == SDLK_e)
                  m_vecIslands.emplace_back(fhl::Vec2f(1200, sup::getRand(200, 400)));*/
			   switch (event.key.keysym.sym)
			   {
			   case SDLK_SPACE: m_hero.changeState(Hero::State_Jump); break;
			   case SDLK_e: m_vecIslands.emplace_back(fhl::Vec2f(1200, sup::getRand(200, 400))); break;
			   case SDLK_DOWN: 
					if (m_bgMusic.getVolume() > 0.f) m_bgMusic.setVolume(m_bgMusic.getVolume() - 5.f);
					break;
			   case SDLK_UP:
				   if (m_bgMusic.getVolume() < 100.f) m_bgMusic.setVolume(m_bgMusic.getVolume() + 5.f);
				   break;
			   }
               break;
           case SDL_MOUSEBUTTONDOWN:
			   if (m_sphere.getState() == Sphere::State_Idle)
			   {
				   m_sphere.setDirection(countThrowDir());
				   m_sphere.changeState(Sphere::State_Thrown);
			   }
               break;
       }
   }
}

void Game::update()
{
   m_hero.update(dt);
   m_sphere.update(dt);

   if(m_sphere.getState() == Sphere::State_Return &&
      m_hero.isCollision(m_sphere))
   {
      m_sphere.changeState(Sphere::State_Idle);
   }

   for (auto & isl : m_vecIslands)
   {
	   isl.update(dt);
	   isl.move(-dt * 1200.f);

	   auto & coins = isl.getCoins();

		coins.erase(
			 std::remove_if(coins.begin(), coins.end(),
				  [&](Coin & _c) { return _c.isCollision(m_hero) || _c.isCollision(m_sphere); }),
			 coins.end());
   }

	m_vecIslands.erase(
		 std::remove_if(m_vecIslands.begin(), m_vecIslands.end(),
			  [](const Island & _isl) { return _isl.getPosition().x() < -200.f; }),
		 m_vecIslands.end());

   if(m_hero.getPosition().y() > WIN_Y)
   {
      m_hero.setPosY(WIN_Y);
      m_hero.changeState(Hero::State_Move);
   }

   int collidingIslandNum = isHeroOnIsland();
   static auto onIsland = [&]() -> bool { return collidingIslandNum >= 0; };

   if(m_hero.getState() == Hero::State_Move &&
      m_hero.getPosition().y() < WIN_Y &&
      !onIsland())
   {
      m_hero.changeState(Hero::State_Fall);
   }

   if(m_hero.getState() == Hero::State_Fall &&
      onIsland() )
   {
      m_hero.setPosY(m_vecIslands[collidingIslandNum].getSurfaceHeight() + 5.f);
      m_hero.changeState(Hero::State_Move);
   }

   m_cliff.update(dt);

	fhl::Light light = fhl::Light::spot(fhl::Vec3f(m_hero.getPosition(), 500.f), fhl::Vec3f::forward(), fhl::Color(129.f / 255, 240.f / 255, 232.f / 255), 2.5f, 1.6f, 1e-4f, 1e-6f);
	fhl::Light light2 = fhl::Light::infinite({ -0.4f, 0.5f, -0.1f }, fhl::Color(118.f / 255, 196.f / 255, 245.f/ 255));
	fhl::Light light3 = fhl::Light::spot(fhl::Vec3f(m_sphere.getPosition(), 500.f), fhl::Vec3f::forward(), fhl::Color::Yellow, 2.5f, .7f, 1e-4f, 1e-6f);
   std::vector<fhl::Light> lights;

   for (const Island & isl : m_vecIslands)
   {
	   auto && v = isl.getLights();
	   lights.insert(lights.begin(), v.begin(), v.end());
   }
   lights.insert(lights.begin(), { light, light2 });
   if (m_sphere.getState() != Sphere::State_Idle)
	   lights.push_back(light3);

   m_cliff.setLights(lights);

	m_spr.rotate(100.f * dt);
}

void Game::draw()
{
	constexpr fhl::Color rtCleanColor(0, 0, 1, 0.3f);
	m_rt.clearColor(rtCleanColor);
	m_rt.renderToTex(m_sphere);

	fhl::Renderer::clearColor();
   m_renderer.clearColor(fhl::Vec4f(0.f, 0.f, 0.f, 1.f));

   m_renderer.renderToTex(m_cliff);

   for(Island & isl : m_vecIslands)
      m_renderer.renderToTex(isl);
   m_renderer.renderToTex(m_hero);
   if(m_sphere.getState() != Sphere::State_Idle)
		m_renderer.renderToTex(m_sphere);

	//m_renderer.renderToTex(m_spr);

   m_renderer.renderToScreen();

   SDL_GL_SwapWindow(m_window);
}

int Game::isHeroOnIsland()
{
   int num = 0;
   for(Island& isl : m_vecIslands)
   {
		 if (m_hero.isCollision(isl))
			  return num;
      num++;
   }
   return -1;
}

fhl::Vec2f Game::countThrowDir()
{
	fhl::Vec2f dir = (fhl::Vec2f(Input::getMousePosition()) - m_hero.getPosition()).normalized();

   return dir;
}
