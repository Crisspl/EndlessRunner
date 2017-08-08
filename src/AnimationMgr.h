#ifndef ANIMATIONMGR_H
#define ANIMATIONMGR_H

#include <FHL/Utility/Rect.h>
#include <FHL/Graphics/Sprite.h>
#include <FHL/Maths/Vec2.h>

#include <vector>

class AnimationMgr
{
public:
	template<typename ...FramesPerState>
	AnimationMgr::AnimationMgr(fhl::Sprite * _sprt, float _interval, fhl::Vec2u _size, FramesPerState... _framesPerState) :
		m_ptrSprite(_sprt),
		m_interval(_interval),
		m_frameSize(_size),
		isColumnwise(false),
		m_framesPerState{ static_cast<std::size_t>(_framesPerState)... }
	{}

public:
	void update(float _dt);

	AnimationMgr & setState(std::size_t r) { m_currentState = r; m_frameCounter = 0; return *this; }
	AnimationMgr & setFrameSize(const fhl::Vec2f & size) { m_frameSize = size; return *this; }
	AnimationMgr & setColumnwise(bool cw) { isColumnwise = cw; return *this; }

private:
	fhl::Sprite * m_ptrSprite;
	float m_currentFrameTime;
	std::size_t m_currentState;
	std::size_t m_frameCounter;
	float m_interval;
	fhl::Vec2u m_frameSize;
	bool isColumnwise;
	const std::vector<std::size_t> m_framesPerState;
};

#endif
