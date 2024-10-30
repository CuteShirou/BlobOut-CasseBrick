#include "pch.h"
#include "Window.h"
#include "Ball.h"
#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    // Initialisation de la fenêtre et de la balle
    Window window;
    Ball ball(sf::Vector2f(100.0f, 100.0f), sf::Vector2f(1.0f, 1.0f), 5.0f);

    // Création de la fenêtre SFML
    window.CreateWindow(800, 600);

    // Boucle principale
    while (window.IsRunning()) {
        // Gestion des événements
        window.PollEvents();

        // Déplacement de la balle
        ball.Move();

        // Efface la fenêtre avant de dessiner
        window.Clear();

        // Dessin de la balle
        ball.SpriteDraw("../../../src/cassebrick/ball.png");

        // Affiche ce qui a été dessiné
        window.Display();
    }

#ifdef _DEBUG
    _CrtDumpMemoryLeaks();
#endif

    return 0;
}
