#ifndef SCORE_H
#define SCORE_H

#include <SFML/Graphics.hpp>
#include <string>

class Score {
protected:
    int score;                    // Variable pour stocker le score actuel
    sf::Text scoreText;           // Texte pour afficher le score
    sf::Font font;                // Police pour le texte du score
    float multiplier;


public:
    // Constructeur
    Score();

    // Méthodes pour gérer le score
    void Reset();                 // Remet le score à zéro
    void Increase(int points);    // Augmente le score d'un certain nombre de points
	sf::Text GetScoreText();      // Getter pour obtenir le texte du score
	void SetTextPos(sf::Vector2f pos); // Setter pour définir la position du texte (scoreText.setPosition(pos);)
    void AddMultiplier(float multiplier);
    void SetMultiplier(float multiplier);
    // Getter pour obtenir le score actuel
    int GetScore() const;
};

#endif // SCORE_H