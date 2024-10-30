#include "pch.h"
#include "main.h"
#include "Window.h"
#include "Paddle.h"
#include "Brick.h"

#include <iostream>
#include <vector>

int main()
{
    Window window;
    window.CreateWindow(800, 600);

    // Vecteur pour stocker les briques
    std::vector<Brick> bricks;

    // Dimensions de la brique et configuration du motif
    sf::Vector2<float> brickSize(80, 30); // Taille de chaque brique
    sf::Color brickColor = sf::Color::Red; // Couleur des briques
    int rows = 5; // Nombre de lignes de briques
    int cols = 8; // Nombre de colonnes de briques
    float startX = 50; // Position de départ en X
    float startY = 50; // Position de départ en Y
    float spacingX = 10; // Espace entre les briques en X
    float spacingY = 10; // Espace entre les briques en Y

    // Création du motif de briques
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            float x = startX + col * (brickSize.x + spacingX);
            float y = startY + row * (brickSize.y + spacingY);
            bricks.emplace_back(sf::Vector2<float>(x, y), brickSize, brickColor);
        }
    }

    while (true) {
        window.PollEvents();
        window.Clear();

        // Dessiner chaque brique
        for (auto& brick : bricks) {
            if (!brick.IsDestroyed()) {
                sf::Sprite sprite = brick.SpriteDraw("../../../src/cassebrick/BRICK.png");
                sprite.setPosition(brick.GetPos());
                window.Draw(sprite);
            }
        }

        window.Display();
    }

#ifdef _DEBUG
    _CrtDumpMemoryLeaks();
#endif

    return 0;
}
