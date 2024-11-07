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
#include "Sound.h"

void init(Score& score, Window& window, Paddle* paddle, Ball* ball, std::vector<Brick>& bricks) {
  
    //init variable paddle and ball
    sf::Vector2f paddlePos(350, 500);
    sf::Vector2f ballPos(400, 400); // Position initiale de la balle
    sf::Vector2f ballDir(0.0f, -1.0f); // Direction initiale de la balle
    float ballSpeed = 5.0f; // Vitesse de la balle

    //init paddle and ball
    paddle->SetPos(paddlePos);
    paddle->SetScale(1, 1.2);
    ball->SetPos(ballPos);
    ball->setDir(ballDir);
    ball->setSpeed(ballSpeed);

    //setup bricks
    int rows = 4; // Nombre de lignes de briques
    int cols = 2; // Nombre de colonnes de briques
    float startX = 10; // Position de départ en X
    float startY = 80; // Position de départ en Y
    sf::Vector2<float> BrickScale(0.5, 0.5); // Taille de chaque brique
    float spacingX = 79; // Espace entre les briques en X
    float spacingY = 35; // Espace entre les briques en Y

    window.SetBackground("../../../src/cassebrick/Wallpaper.png");
  
    //creat and place all the bricks
    int it = 0;
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            float x = startX + col * (BrickScale.x + spacingX);
            float y = startY + row * (BrickScale.y + spacingY);
            bricks.emplace_back(sf::Vector2<float>(x, y), BrickScale);
            bricks[it].SetScale(BrickScale.x, BrickScale.y);
            ++it;
        }
    }
}

bool gameloop(Window& window, Paddle* paddle, Ball* ball, ParticleSystem& particles, sf::Clock& clock, std::vector<Brick>& bricks, Score& score, sf::Text fpsText, Sound collisionSound){

    window.Clear();
    window.PollEvents(paddle);

    sf::Vector2i ballPosInt = static_cast <sf::Vector2i>(ball->GetPos());
    ballPosInt = ballPosInt + sf::Vector2i(ball->GetRectangle().height / 2, ball->GetRectangle().width / 2);
    particles.SetEmitter(window.GetWindow().mapPixelToCoords(ballPosInt));

    sf::Time elapsed = clock.restart();
    particles.Update(elapsed);

    ball->Move(window);

    if (ball->CollisionPaddle(*paddle)) {
        window.MoveWindow();
        ball->IncreaseSpeed(1.03);
        score.SetMultiplier(1.f);
        window.BackgroundChange();
    }


    for (auto it = bricks.begin(); it != bricks.end(); ) {
        it->SpriteDraw("Romain Giovannini le GOAT");
        window.Draw(it->GetSprite());

        if (ball->OnCollision(*it)) {
            it->Destroy();
            it = bricks.erase(it);

            score.Increase(100);
            score.AddMultiplier(1.1);
            collisionSound.PlaySound();

            window.ShakeWindow();
          
            if (bricks.size() == 0) {
                return false;
            }
        }
        else {
            ++it;
        }
    }
    window.DrawParticle(particles);
    ball->SpriteDraw("../../../src/cassebrick/ball.png");
    paddle->SpriteDraw("../../../src/cassebrick/paddle.png");
    window.Draw(ball->GetSprite());
    window.Draw(paddle->GetSprite());
    window.DrawScore(score.GetScoreText());
    window.Update(500, 15);
    window.DrawScore(score.GetScoreText());
    window.DrawScore(fpsText);

    window.Display();

    return true;
}

int main()
{
    Menu* menu = new Menu();
    Score score;
    Window window;
    Paddle* paddle = new Paddle(sf::Vector2(0.0f, 0.0f));
    Ball* ball = new Ball(sf::Vector2(0.0f, 0.0f), sf::Vector2(0.0f, 0.0f), 0);
    ParticleSystem particles(5000);
    std::vector<Brick> bricks;
    sf::Clock clock;
    sf::Clock fpsClock;
    sf::Text fpsText;
    sf::Font font;
    font.loadFromFile("../../../src/cassebrick/CyborgPunk.ttf");
    fpsText.setFont(font);
    fpsText.setCharacterSize(12);
    fpsText.setFillColor(sf::Color(255, 255, 255, 100));
    fpsText.setPosition(700, 5);
    fpsText.setString(sf::String("FPS : 0"));
    Sound collisionSound("../../../src/cassebrick/Augh.wav");
    Sound BackgroundMusic("../../../src/cassebrick/BackgroundMusic.wav");
    collisionSound.SetVolume(60);
    BackgroundMusic.SetVolume(100);
    int gameState = 0;

    window.CreateWindow(800, 600);
  
    auto fpsTime = std::chrono::system_clock::now();
    float fps;
    
    BackgroundMusic.PlaySound();

    // Boucle principale
    while (window.GetWindow().isOpen()) {

        // GetFPS
        auto currentTime = std::chrono::system_clock::now();
        fps = 1.0f / clock.getElapsedTime().asSeconds();
        if (currentTime - fpsTime > std::chrono::seconds(1)) {
            fpsTime = currentTime;
            fpsText.setString(sf::String("FPS : " + std::to_string((int)fps)));
        }
      
        if (gameState == 0) {
            menu->RunMenu(window, fpsText);
            gameState = menu->GetState();
            if (gameState == 1) {
                init(score, window, paddle, ball, bricks);
            }
        }

        // Boucle de jeu
        else if (gameState == 1) {
            if (!gameloop(window, paddle, ball, particles, clock, bricks, score, fpsText, collisionSound)) {

                std::cout << "Ended";
                gameState = 0;
                menu->SetState(0);
                score.SaveScore();
				score.Reset();
            }
        }
        else if (gameState == 2) {
            // Faire 5 rectangles pour les 5 meilleurs scores (display only)
            std::vector<int> topScores = score.GetTopScores();
            std::cout << "Les 5 meilleurs scores :\n";
            for (int s : topScores) {
                std::cout << s << std::endl;
            }

            return 0;
        }
        
    }

#ifdef _DEBUG
    _CrtDumpMemoryLeaks();
#endif
    return 0;
}
