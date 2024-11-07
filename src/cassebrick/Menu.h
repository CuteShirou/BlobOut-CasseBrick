#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Window.h"

class Menu {
    int pos;
    int gameState = 0;
    bool pressed, theselect;

    sf::RectangleShape* winclose;
    sf::RectangleShape* playRec;
    sf::RectangleShape* scoresRec;
    sf::RectangleShape* optionsRec;
    sf::RectangleShape* quitRec;

    sf::Font* font;
    sf::Texture* image;
    sf::Sprite* bg;

    sf::Vector2i pos_mouse;
    sf::Vector2f mouse_coord;

    std::vector<const char*> options;
    std::vector<sf::Vector2f> coords;
    std::vector<sf::Text> texts;
    std::vector<std::size_t> sizes;


protected:
    void LoopEvents(Window& window);
    void DrawAll(Window& window, sf::Text fpsText);

public:
    Menu(Window& window);
    ~Menu();
    void SetValues(Window& window);
    void RunMenu(Window& window, sf::Text fpsText);
    int GetState();
    void SetState(int state);
};