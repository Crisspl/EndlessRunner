#include "SoundMgr.h"

std::map<std::string, SoundMgr::SoundPair> SoundMgr::m_buffers;

sf::Sound & SoundMgr::loadSound(std::string _path, std::string _name)
{
	m_buffers.emplace(_name, _path);
	return m_buffers[_name].s;
}

sf::Sound & SoundMgr::getSound(std::string _name)
{
	return m_buffers[_name].s;
}

bool SoundMgr::isSoundBufferLoaded(std::string _name)
{
	return m_buffers.find(_name) != m_buffers.end();
}

