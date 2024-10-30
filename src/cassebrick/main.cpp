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
    sf::Vector2<float> BrickScale(0.5, 0.5); // Taille de chaque brique
    int rows = 5; // Nombre de lignes de briques
    int cols = 13; // Nombre de colonnes de briques
    float startX = 10; // Position de d�part en X
    float startY = 10; // Position de d�part en Y
    float spacingX = 79; // Espace entre les briques en X
    float spacingY = 55; // Espace entre les briques en Y

    // Cr�ation du motif de briques
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            float x = startX + col * (BrickScale.x + spacingX);
            float y = startY + row * (BrickScale.y + spacingY);
            bricks.emplace_back(sf::Vector2<float>(x, y), BrickScale);
        }
    }

    while (true) {
        window.PollEvents();
        window.Clear();

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
