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

void Sound::playSound() {
    sound.play();
}
