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

    // M�thodes pour g�rer le score
    void Reset();                 // Remet le score � z�ro
    void Increase(int points);    // Augmente le score d'un certain nombre de points
	sf::Text GetScoreText();      // Getter pour obtenir le texte du score
	void SetTextPos(sf::Vector2f pos); // Setter pour d�finir la position du texte (scoreText.setPosition(pos);)
    void AddMultiplier(float multiplier);
    void SetMultiplier(float multiplier);
    // Getter pour obtenir le score actuel
    int GetScore() const;
};

#endif // SCORE_H