#ifndef SOUND_H__
#define SOUND_H__

#include <SFML/Audio.hpp>
#include <string>

class Sound {
public:
	Sound(const std::string& filename);
	void playSound();

protected:
	sf::Sound sound;
	sf::SoundBuffer buffer;
};

#endif