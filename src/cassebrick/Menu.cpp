#include "pch.h"
#include "Menu.h"

Menu::Menu() {
    winclose = new sf::RectangleShape();
    font = new sf::Font();
    image = new sf::Texture();
    bg = new sf::Sprite();

    SetValues();
}

Menu::~Menu() {
    delete winclose;
    delete font;
    delete image;
    delete bg;
}

void Menu::SetValues() {

    pos = 0;
    pressed = theselect = false;
    font->loadFromFile("../../../src/cassebrick/CyborgPunk.ttf");
    image->loadFromFile("../../../src/cassebrick/Background_Menu.png");

    bg->setTexture(*image);

    pos_mouse = { 0,0 };
    mouse_coord = { 0, 0 };
    options = { "Blob Out", "Play", "Scores", "Options", "Quit" };
    texts.resize(5);
    coords = { {365,35},{378,165},{360,235},{350,307},{378,379} };
    sizes = { 15,20,20,20,20 };

    for (std::size_t i{}; i < texts.size(); ++i) {
        texts[i].setFont(*font);
        texts[i].setString(options[i]);
        texts[i].setCharacterSize(sizes[i]);
        texts[i].setOutlineColor(sf::Color::Black);
        texts[i].setPosition(coords[i]);
    }
    texts[1].setOutlineThickness(4);
    pos = 1;

    winclose->setSize(sf::Vector2f(38, 38));
    winclose->setPosition(723, 20);
    winclose->setFillColor(sf::Color::Transparent);

}

void Menu::LoopEvents(Window& window) {
    sf::Event event;
    while (window.GetWindow().pollEvent(event)) {

        pos_mouse = sf::Mouse::getPosition(window.GetWindow());
        mouse_coord = window.GetWindow().mapPixelToCoords(pos_mouse);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !pressed) {
            if (pos < 4) {
                ++pos;
                pressed = true;
                texts[pos].setOutlineThickness(4);
                texts[pos - 1].setOutlineThickness(0);
                pressed = false;
                theselect = false;
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !pressed) {
            if (pos > 1) {
                --pos;
                pressed = true;
                texts[pos].setOutlineThickness(4);
                texts[pos + 1].setOutlineThickness(0);
                pressed = false;
                theselect = false;
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && !theselect) {
            theselect = true;
            if (pos == 4) {
                window.GetWindow().close();
            }
            if (pos == 1) {
                gameState = 1;
            }
            if (pos == 2) {
                gameState = 2;
            }
            if (pos == 3) {
                gameState == 3;
            }
        }

        else if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if (winclose->getGlobalBounds().contains(mouse_coord)) {
                //std::cout << "Close the window!" << '\n';
                window.GetWindow().close();
            }
        }
    }
}

void Menu::DrawAll(Window& window, sf::Text fpsText) {
    window.GetWindow().clear();
    window.GetWindow().draw(*bg);
    for (auto t : texts) {
        window.GetWindow().draw(t);
    }
    window.GetWindow().display();
    window.DrawScore(fpsText);
}

int Menu::GetState()
{
    return gameState;
}

void Menu::SetState(int state)
{
    gameState = state;
}

void Menu::RunMenu(Window& window, sf::Text fpsText) {
    LoopEvents(window);
    DrawAll(window, fpsText);
}