#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <vector>
#include <memory>

#include <SFML/Audio/Music.hpp>

#include <FHL/Utility/Clock.h>
#include <FHL/Graphics/Configurator.h>
#include <FHL/Graphics/ResMgr.h>
#include <FHL/Graphics/VertexArray.h>
#include <FHL/Graphics/ColoredRect.h>
#include <FHL/Graphics/Model.h>

#include "Global.h"
#include "Hero.h"
#include "Sphere.h"
#include "Island.h"
#include "EndlessCliff.h"
#include "ScreenRenderer.h"


class Game
{
private:
	Game();

public:
	static Game& get();
	void run();
	static void initSystems();

private:
	void mainLoop();
	void handleEvents();
	void update();
	void draw();

	int isHeroOnIsland(); /* If hero collides an island - returns its number in container, otherwise returns -1 */
	fhl::Vec2f countThrowDir();

private:
	static SDL_Window* m_window;
	static SDL_GLContext m_context;
	ScreenRenderer m_renderer;

	Hero m_hero;
	Sphere m_sphere;
	std::vector<Island> m_vecIslands;
	EndlessCliff m_cliff;
	fhl::RenderTexture m_rt;
	fhl::Sprite m_spr;

	sf::Music m_bgMusic;

	fhl::Clock m_timer;
	float dt;

	bool m_running;

public:
	constexpr static GLuint WIN_X = 800, WIN_Y = 600;
};

#endif
