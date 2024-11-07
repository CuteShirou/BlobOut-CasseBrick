#include "pch.h"
#include <iostream>
#include "Score.h"

// Constructeur : initialise le score et charge la police
Score::Score() : score(0), multiplier(1.f) {
    // Charge la police (assurez-vous que "arial.ttf" est bien dans votre dossier de projet)
    if (!font.loadFromFile("../../../../../src/cassebrick/CyborgPunk.ttf")) {
        // Gestion d'erreur si le fichier de police ne peut être chargé
		std::cout << "Error loading font\n";
    }

    // Configuration de l'objet texte pour le score
    scoreText.setFont(font);
    scoreText.setString(sf::String("Score: 0"));
    scoreText.setCharacterSize(20);                         // Taille du texte
    scoreText.setFillColor(sf::Color(255, 255, 255, 100));  // Couleur du texte + Opacité
    scoreText.setPosition(5, 5);                            // Position du texte dans la fenêtre
}
    
// Remet le score à zéro
void Score::Reset() {
    score = 0;
    scoreText.setString("Score: " + std::to_string(score));
    SetMultiplier(1.f);
}

// Augmente le score d'un certain nombre de points
void Score::Increase(int points) {
    score += points * multiplier;
    scoreText.setString("Score: " + std::to_string(score));
}

sf::Text Score::GetScoreText()
{
    return scoreText;
}

void Score::SetTextPos(sf::Vector2f pos)
{
	scoreText.setPosition(pos);
}

void Score::AddMultiplier(float multiplier_)
{
    multiplier += multiplier_;
}

void Score::SetMultiplier(float multiplier_)
{
    multiplier = multiplier_;
}

// Retourne le score actuel
int Score::GetScore() const {
    return score;
}

void Score::SaveScore() {
    allScores.push_back(score);  // Ajoute le score actuel dans le vecteur
}

std::vector<int> Score::GetTopScores() {
    std::vector<int> topScores = allScores;  // Copie des scores en mémoire pour le tri

    std::sort(topScores.begin(), topScores.end()); // Trie les scores en ordre croissant

    if (topScores.size() > 5) {
        topScores.resize(5); // Conserve seulement les 5 meilleurs scores
    }

    return topScores;
}
