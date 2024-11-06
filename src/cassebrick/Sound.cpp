#include "pch.h"
#include <iostream>
#include <string>   
#include "Sound.h"

Sound::Sound(const std::string& filepath) {
    // Charger le fichier audio dans le buffer
    if (!buffer.loadFromFile(filepath)) {
        std::cerr << "Erreur : impossible de charger le fichier audio " << filepath << std::endl;
    }
    sound.setBuffer(buffer); // Associer le buffer au son
}

void Sound::PlaySound() {
    sound.play();
}

void Sound::SetVolume(float Volume)
{
	sound.setVolume(Volume);
}

void Sound::AddSound(const sf::SoundBuffer& buffer)
{
    sf::Sound sound;
    sound.setBuffer(buffer);  // Associe le buffer au son
    sounds.push_back(sound);  // Ajoute le son à la liste
}