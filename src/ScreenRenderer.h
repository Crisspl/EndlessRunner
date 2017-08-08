#ifndef SCREENRENDERER_H
#define SCREENRENDERER_H

#include <FHL/Graphics/ResMgr.h>
#include <FHL/Graphics/RenderTexture.h>
#include <FHL/Graphics/Shader.h>
#include <FHL/Graphics/Renderable.h>
#include <FHL/Graphics/Configurator.h>
#include <FHL/Graphics/Sprite.h>

class ScreenRenderer
{
public:
   ScreenRenderer();

public:
   void clearColor(fhl::Vec4f _color);
   void renderToTex(fhl::Renderable & _obj);
   void renderToScreen();

private:
   fhl::Shader& m_shader;
   fhl::RenderTexture m_renderTex;
   fhl::Sprite m_screen;
};

#endif // SCREENRENDERER_H
