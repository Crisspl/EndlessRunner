#ifndef ENDLESSCLIFF_H
#define ENDLESSCLIFF_H

#include <FHL/Graphics/Model.h>
#include <FHL/Graphics/Renderer.h>

class EndlessCliff
	: public fhl::Renderable
{
public:
	EndlessCliff();

	void render(const fhl::RenderConf &) const override;
	void update(float _dt);
	void setLights(std::vector<fhl::Light> & _lights);

private:
	fhl::Model m_model;
};

#endif // ENDLESSCLIFF_H
