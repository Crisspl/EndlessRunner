#include "ScreenRenderer.h"

#include <FHL/Graphics/Renderer.h>

ScreenRenderer::ScreenRenderer()
      : m_shader(fhl::ResMgr::loadShader("screenShader", "Resources/ShaderSrcs/screen_vs.glsl", "Resources/ShaderSrcs/screen_fs.glsl", fhl::Shader::FromFile)),
        m_renderTex(fhl::ResMgr::createTexture("screenTex", fhl::Vec2i(800, 600))),
        m_screen(m_renderTex.getTexture())
{
   m_screen.setShader(m_shader);
   m_screen.setSize({2, 2});
   m_screen.setTextureRect(fhl::Rect(m_renderTex.getTexture().getSize()));
}

void ScreenRenderer::clearColor(fhl::Vec4f _color)
{
   m_renderTex.clearColor(_color);
}

void ScreenRenderer::renderToTex(fhl::Renderable & _obj)
{
   m_renderTex.renderToTex(_obj);
}

void ScreenRenderer::renderToScreen()
{
	fhl::Renderer::render(m_screen);
}
