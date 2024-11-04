#include "pch.h"
#include <iostream>
#include "Score.h"

// Constructeur : initialise le score et charge la police
Score::Score() : score(0) {
    // Charge la police (assurez-vous que "arial.ttf" est bien dans votre dossier de projet)
    if (!font.loadFromFile("../../../src/cassebrick/airstrike.ttf")) {
        // Gestion d'erreur si le fichier de police ne peut être chargé
		std::cout << "Error loading font\n";
    }

    // Configuration de l'objet texte pour le score
    scoreText.setFont(font);
    scoreText.setString(sf::String("Score: 0"));
    scoreText.setCharacterSize(100);            // Taille du texte
    scoreText.setFillColor(sf::Color::White);   // Couleur du texte
    scoreText.setPosition(10, 10);              // Position du texte dans la fenêtre
}

// Remet le score à zéro
void Score::Reset() {
    score = 0;
    scoreText.setString("Score: " + std::to_string(score));
}

// Augmente le score d'un certain nombre de points
void Score::Increase(int points) {
    score += points;
    scoreText.setString("Score: " + std::to_string(score));
}

sf::Text Score::GetScoreText()
{
    return sf::Text();
}

void Score::SetTextPos(sf::Vector2f pos)
{
	scoreText.setPosition(pos);
}

// Retourne le score actuel
int Score::GetScore() const {
    return score;
}