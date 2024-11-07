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

void init(Score& score, Window& window, Paddle* paddle, Ball* ball, std::vector<Brick>& bricks, Sound& collisionSound) {
  
    int windowWidth = window.GetWidth();
    int windowHeight = window.GetHeight();

    //init variable paddle and ball
    sf::Vector2f paddlePos (windowWidth/2 - (paddle->GetSprite().getPosition().x) / 2, windowHeight*0.95);
    sf::Vector2f ballPos(windowWidth / 2 - (ball->GetSprite().getPosition().x) / 2, windowHeight * 0.8); // Position initiale de la balle
    sf::Vector2f ballDir(0.0f, -1.0f); // Direction initiale de la balle
    float ballSpeed = 5.0f; // Vitesse de la balle

    //init paddle and ball
    paddle->SetPos(paddlePos);
    paddle->SetScale(1, 1.2);
    ball->SetPos(ballPos);
    ball->setDir(ballDir);
    ball->setSpeed(ballSpeed);

    //setup bricks
    int rows = 6; // Nombre de lignes de briques
    int cols = 10; // Nombre de colonnes de briques
    window.SetBackground("../../../../../src/cassebrick/Wallpaper.png");
  
    float spacingX = windowWidth * 0.05 / rows;
    float spacingY = windowHeight * 0.03 / cols;

    //setup sound
    collisionSound.SetVolume(80);

    // Reset score at each start
    score.Reset();

    // Base dimensions for the brick image
    float baseBrickWidth = 128.0f;
    float baseBrickHeight = 64.0f;

    // Available width and height for brick placement
    float availableWidth = windowWidth - ((cols + 1) * spacingX);
    float availableHeight = windowHeight * 0.8 / 2 - ((rows + 1) * spacingY);

    // Calculate scaling factors based on the available space and base brick size
    float scaleX = (availableWidth / (cols * baseBrickWidth));
    float scaleY = (availableHeight / (rows * baseBrickHeight));

    // Create and place bricks
    bricks.clear();
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            float x = spacingX + col * (baseBrickWidth * scaleX + spacingX);
            float y = windowHeight * 0.1 + spacingY + row * (baseBrickHeight * scaleY + spacingY);
            bricks.emplace_back(sf::Vector2f(x, y), sf::Vector2f(baseBrickWidth, baseBrickHeight));
            bricks.back().SetScale(scaleX, scaleY);  // Apply the scaling
        }
    }
}

bool gameloop(Window& window, Paddle* paddle, Ball* ball, ParticleSystem& particles, sf::Clock& clock, std::vector<Brick>& bricks, Score& score, sf::Text fpsText, Sound& collisionSound){

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
    ball->SpriteDraw("../../../../../src/cassebrick/ball.png");
    paddle->SpriteDraw("../../../../../src/cassebrick/paddle.png");
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
    Window window;
    window.CreateWindow(800, 600);
    int windowHeight = window.GetHeight();
    int windowWidth = window.GetWidth();
    Score score;
    Menu* menu = new Menu(window);
    Paddle* paddle = new Paddle(sf::Vector2(0.0f, 0.0f));
    Ball* ball = new Ball(sf::Vector2(0.0f, 0.0f), sf::Vector2(0.0f, 0.0f), 0);
    ParticleSystem particles(5000);
    std::vector<Brick> bricks;
    sf::Clock clock;
    sf::Clock fpsClock;
    sf::Text fpsText;
    sf::Font font;
    font.loadFromFile("../../../../../src/cassebrick/CyborgPunk.ttf");
    fpsText.setFont(font);
    fpsText.setCharacterSize(12);
    fpsText.setFillColor(sf::Color(255, 255, 255, 100));
    fpsText.setString(sf::String("FPS : 0"));
    sf::Text messcores(sf::String("Mes Scores"), font, windowHeight * 0.033);
    std::vector<sf::Text> topScoreTexts(5, sf::Text(sf::String("0"), font, windowHeight * 0.033));
    messcores.setPosition(310, 100);
    Sound collisionSound("../../../src/cassebrick/Augh.wav");
    Sound BackgroundMusic("../../../src/cassebrick/BackgroundMusic.wav");
    collisionSound.SetVolume(60);
    BackgroundMusic.SetVolume(100);
    int gameState = 0;
    
  
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
            fpsText.setPosition(window.GetWidth() - 100, 5);
        }
      
        if (gameState == 0) {
            menu->RunMenu(window, fpsText);
            gameState = menu->GetState();
            if (gameState == 1) {
                init(score, window, paddle, ball, bricks, collisionSound);
            }
        }

        // Boucle de jeu
        else if (gameState == 1) {
            if (!gameloop(window, paddle, ball, particles, clock, bricks, score, fpsText, collisionSound)) {

                gameState = 0;
                menu->SetState(0);
                score.SaveScore();
            }
        }

        else if (gameState == 2) {
            sf::Event event;
            window.Clear();
            window.SetBackground("../../../src/cassebrick/Scores.png");
            while (window.GetWindow().pollEvent(event)) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                    gameState = 0;
                    menu->SetState(0);
                }
            }

            topScoreTexts[0].setString(sf::String(std::to_string(score.GetTopScores()[0])));
            topScoreTexts[1].setString(sf::String(std::to_string(score.GetTopScores()[1])));
            topScoreTexts[2].setString(sf::String(std::to_string(score.GetTopScores()[2])));
            topScoreTexts[3].setString(sf::String(std::to_string(score.GetTopScores()[3])));
            topScoreTexts[4].setString(sf::String(std::to_string(score.GetTopScores()[4])));

            topScoreTexts[0].setPosition(windowWidth * 0.4375f, windowHeight * 0.3833f);
            topScoreTexts[1].setPosition(windowWidth * 0.4375f, windowHeight * 0.5f);
            topScoreTexts[2].setPosition(windowWidth * 0.4375f, windowHeight * 0.6167f);
            topScoreTexts[3].setPosition(windowWidth * 0.4375f, windowHeight * 0.725f);
            topScoreTexts[4].setPosition(windowWidth * 0.4375f, windowHeight * 0.8417f);

            window.DrawScore(messcores);
            window.DrawScore(topScoreTexts[0]);
            window.DrawScore(topScoreTexts[1]);
            window.DrawScore(topScoreTexts[2]);
            window.DrawScore(topScoreTexts[3]);
            window.DrawScore(topScoreTexts[4]);

            window.Display();
        }

        else if (gameState == 3) {

            
            if (gameState == 1) {
                menu->SetValues(window);
            }
        }
        
    }

#ifdef _DEBUG
    _CrtDumpMemoryLeaks();
#endif
    return 0;
}
