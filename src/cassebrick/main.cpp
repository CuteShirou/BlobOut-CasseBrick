#include "pch.h"
#include "Window.h"
#include <iostream>
#include <vector>

#include "Paddle.h"
#include "Brick.h"

int main()
{
    sf::Vector2f paddlePos(350, 500);
    Paddle* paddle = new Paddle(paddlePos);

    Window window;
    window.CreateWindow(800, 600);

    // Initialisation de la balle
    sf::Vector2f ballPos(400, 300); // Position initiale de la balle
    sf::Vector2f ballDir(0.5f, -0.5f); // Direction initiale de la balle
    float ballSpeed = 5.0f; // Vitesse de la balle
    Ball ball(ballPos, ballDir, ballSpeed); // Création de la balle

    // Vecteur pour stocker les briques
    std::vector<Brick> bricks;

    // Dimensions de la brique et configuration du motif
    sf::Vector2<float> BrickScale(0.5, 0.5); // Taille de chaque brique
    int rows = 5; // Nombre de lignes de briques
    int cols = 13; // Nombre de colonnes de briques
    float startX = 10; // Position de départ en X
    float startY = 80; // Position de départ en Y
    float spacingX = 79; // Espace entre les briques en X
    float spacingY = 35; // Espace entre les briques en Y

    // Création du motif de briques
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            float x = startX + col * (BrickScale.x + spacingX);
            float y = startY + row * (BrickScale.y + spacingY);
            bricks.emplace_back(sf::Vector2<float>(x, y), BrickScale);
        }
    }

    // Boucle principale
    while (true) {
        window.Clear();
        window.PollEvents(paddle);

        // Mise à jour et dessin de la balle
        ball.Move(window); // Déplace la balle en fonction des bordures
        ball.SpriteDraw("../../../src/cassebrick/ball.png"); // Chemin de texture
        window.Draw(ball.GetSprite()); // Dessin de la balle

        // Mise à jour et dessin du paddle
        paddle->SpriteDraw("../../../src/cassebrick/paddle.png");
        paddle->SetScale(1, 1.2);
        window.Draw(paddle->GetSprite());

        // Dessiner chaque brique
        for (auto& brick : bricks) {
            if (!brick.IsDestroyed()) {
                brick.SpriteDraw("../../../src/cassebrick/BRICK.png");
                brick.SetScale(BrickScale.x, BrickScale.y);
                brick.SetPos(brick.GetPos());
                window.Draw(brick.GetSprite());
            }
        }

        window.Display();
    }

#ifdef _DEBUG
    _CrtDumpMemoryLeaks();
#endif

    return 0;
}
