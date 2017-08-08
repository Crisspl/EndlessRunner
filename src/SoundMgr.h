#ifndef SOUNDMGR_H
#define SOUNDMGR_H

#include <map>

#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>

#include <FHL/Utility/Debug.h>

class SoundMgr
{
	struct SoundPair
	{
		SoundPair() = default;
		SoundPair(std::string _path) : s(sb)
		{
			sb.loadFromFile(_path);
		}

		sf::SoundBuffer sb;
		sf::Sound s;
	};

public:
	SoundMgr() = delete;

	static sf::Sound & loadSound(std::string _path, std::string _name);
	static sf::Sound & getSound(std::string _name);
	static bool isSoundBufferLoaded(std::string _name);

private:
	static std::map<std::string, SoundPair> m_buffers;
};

#endif // SOUNDMGR_H
