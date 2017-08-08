#include "AnimationMgr.h"

void AnimationMgr::update(float _dt)
{
	if (!m_ptrSprite->getTexture())
		return;

	m_currentFrameTime += _dt;
	if (m_currentFrameTime >= m_interval)
	{
		m_currentFrameTime = 0;
		fhl::Vec2u v = isColumnwise ? fhl::Vec2u{m_currentState, m_frameCounter} : fhl::Vec2u{m_frameCounter, m_currentState};
		m_ptrSprite->setTextureRect(fhl::Rect(v * m_frameSize, m_frameSize));

		if (++m_frameCounter == m_framesPerState.at(m_currentState))
			m_frameCounter = 0;
	}
}
