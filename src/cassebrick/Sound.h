#ifndef SOUND_H__
#define SOUND_H__

#include <SFML/Audio.hpp>
#include <string>

class Sound {
public:
	Sound(const std::string& filename);
	void PlaySound();
	void SetVolume(float Volume);
	void AddSound(const sf::SoundBuffer& buffer);

protected:
	sf::Sound sound;
	sf::SoundBuffer buffer;
	std::vector<sf::Sound> sounds;
};

#endif