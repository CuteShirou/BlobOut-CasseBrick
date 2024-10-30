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
    sf::Vector2<float> SetScale(1, 2); // Taille de chaque brique
    int rows = 5; // Nombre de lignes de briques
    int cols = 8; // Nombre de colonnes de briques
    float startX = 10; // Position de départ en X
    float startY = 10; // Position de départ en Y
    float spacingX = 90; // Espace entre les briques en X
    float spacingY = 90; // Espace entre les briques en Y

    // Création du motif de briques
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            float x = startX + col * (SetScale.x + spacingX);
            float y = startY + row * (SetScale.y + spacingY);
            bricks.emplace_back(sf::Vector2<float>(x, y), SetScale);
        }
    }

    while (true) {
        window.PollEvents();
        window.Clear();

        // Dessiner chaque brique
        for (auto& brick : bricks) {
            if (!brick.IsDestroyed()) {
                brick.SpriteDraw("../../../src/cassebrick/BRICK.png");
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
