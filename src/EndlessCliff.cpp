#include "EndlessCliff.h"

#include <FHL/Graphics/ResMgr.h>

EndlessCliff::EndlessCliff()
	: m_model(fhl::ResMgr::loadModelData("cliffModel", "Resources/cliff/Cliff_new.obj"))
{
	m_model.setScale(fhl::Vec3f(12.f));
	m_model.setPosition({ (m_model.getSize() * m_model.getScale()).x() / 2.f - 50.f, 80.f, 0 });
	m_model.setShader(fhl::UsingShader::Light);
}

void EndlessCliff::render(const fhl::RenderConf &) const
{
	fhl::Renderer::render(m_model);
	fhl::RenderConf conf;
	conf += m_model.calcModifiedRenderMatrices((m_model.getSize() * m_model.getScale()).x() * fhl::Vec3f::right() * 0.5f, fhl::Vec3f::one(), fhl::Quaternion::identity());
	conf += m_model.getLights();
	fhl::Renderer::render(m_model, conf);
}

void EndlessCliff::update(float _dt)
{
	m_model.move(fhl::Vec3f::left() * 60 * _dt);
}

void EndlessCliff::setLights(std::vector<fhl::Light> & _lights)
{
	m_model.setLights(_lights.begin(), _lights.end());
}
