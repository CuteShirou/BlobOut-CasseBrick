#include "pch.h"
#include <iostream>
#include <vector>
#include "Window.h"
#include "Paddle.h"
#include "Brick.h"
#include "Ball.h"
#include "Score.h"
#include "Particle.h"
#include "Menu.h"

int main()
{
    Window window;
    window.CreateWindow(800, 600);

    Menu* menu = new Menu();

    int gameState = 0;

    if (!window.SetBackground("../../../src/cassebrick/Wallpaper.png")) {
        return -1;
    }
    
    sf::Text fpsText;
    sf::Font font;
    font.loadFromFile("../../../src/cassebrick/CyborgPunk.ttf");
    fpsText.setFont(font);
    fpsText.setCharacterSize(12);
    fpsText.setFillColor(sf::Color(255, 255, 255, 100));
    fpsText.setPosition(700, 5);
    fpsText.setString(sf::String("FPS : 0"));

    Score score;

    auto fpsTime = std::chrono::system_clock::now();
    float fps;

    sf::Vector2f paddlePos(350, 500);
    Paddle* paddle = new Paddle(sf::Vector2(350.f,500.f));

    // Initialisation de la balle
    sf::Vector2f ballPos(400, 400); // Position initiale de la balle
    sf::Vector2f ballDir(0.0f, -1.0f); // Direction initiale de la balle
    float ballSpeed = 5.0f; // Vitesse de la balle
    Ball ball(ballPos, ballDir, ballSpeed); // Création de la balle

    // Particules
    ParticleSystem particles(5000);

    // Vecteur pour stocker les briques
    std::vector<Brick> bricks;

    // Dimensions de la brique et configuration du motif
    sf::Vector2<float> BrickScale(0.5, 0.5); // Taille de chaque brique
    int rows = 5; // Nombre de lignes de briques
    int cols = 10; // Nombre de colonnes de briques
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

    for (auto it = bricks.begin(); it != bricks.end(); ) {
            it->SetScale(BrickScale.x, BrickScale.y);
            it->SetPos(it->GetPos());
            ++it;  // Avancer l'itérateur seulement si aucune suppression
        }

    sf::Clock clock;

    // Boucle principale
    while (window.GetWindow().isOpen()) {
        // Boucle du menu
        if (gameState == 0) {
            auto currentTime = std::chrono::system_clock::now();
            fps = 1.0f / clock.getElapsedTime().asSeconds();
            if (currentTime - fpsTime > std::chrono::seconds(1)) {
                fpsTime = currentTime;
                system("CLS");
            }

            menu->RunMenu(window);
            gameState = menu->GetState();
        }

        // Boucle de jeu
        else if (gameState == 1) {
            window.Clear();
            window.PollEvents(paddle);

            // Mise à jour et dessin de la balle
            ball.Move(window); // Déplace la balle en fonction des bordures
            ball.SpriteDraw("../../../src/cassebrick/ball.png"); // Chemin de texture
            window.Draw(ball.GetSprite()); // Dessin de la balle

            // Mise à jour des particules
            sf::Vector2i ballPosInt = static_cast <sf::Vector2i>(ball.GetPos());
            ballPosInt = ballPosInt + sf::Vector2i(ball.GetRectangle().height / 2, ball.GetRectangle().width / 2);
            particles.SetEmitter(window.GetWindow().mapPixelToCoords(ballPosInt));

            sf::Time elapsed = clock.restart();
            particles.Update(elapsed);
            window.DrawParticle(particles);

            // Mise à jour et dessin du paddle
            paddle->SpriteDraw("../../../src/cassebrick/paddle.png");
            paddle->SetScale(1, 1.2);
            window.Draw(paddle->GetSprite());

            if (ball.CollisionPaddle(*paddle))
            {
                window.MoveWindow();
                ball.IncreaseSpeed(1.03);
                score.SetMultiplier(1.f);
            }

            window.Update(500, 15);

            // Dessiner chaque brique
            for (auto it = bricks.begin(); it != bricks.end(); ) {
                it->SpriteDraw("Romain Giovannini le GOAT");
                window.Draw(it->GetSprite());
                if (ball.OnCollision(*it)) {
                    it->Destroy();  // Détruire la brique
                    it = bricks.erase(it);  // Supprimer la brique et obtenir un nouvel itérateur valide
                    score.Increase(100);  // Augmenter le score
                    window.ShakeWindow();
                    score.AddMultiplier(1.1);
                }
                else {
                    ++it;
                }
            }

            auto currentTime = std::chrono::system_clock::now();
            fps = 1.0f / clock.getElapsedTime().asSeconds();
            if (currentTime - fpsTime > std::chrono::seconds(1)) {
                fpsTime = currentTime;
                fpsText.setString(sf::String("FPS : " + std::to_string((int)fps)));

            }

            window.DrawScore(score.GetScoreText());
            window.DrawScore(fpsText);

            window.Display();
        }
        else if (gameState == 2) {
            // Faire 5 rectangles pour les 5 meilleurs scores (display only)
            std::cout << "Score : ";
            break;
        }
        
    }

#ifdef _DEBUG
    _CrtDumpMemoryLeaks();
#endif
    return 0;
}
