#include "pch.h"
#include "Menu.h"

Menu::Menu(Window& window) {
    winclose = new sf::RectangleShape();
    font = new sf::Font();
    image = new sf::Texture();
    bg = new sf::Sprite();
    playRec = new sf::RectangleShape();
    scoresRec = new sf::RectangleShape();
    optionsRec = new sf::RectangleShape();
    quitRec = new sf::RectangleShape();
    SetValues(window);
}

Menu::~Menu() {
    delete winclose;
    delete font;
    delete image;
    delete bg;
}

void Menu::SetValues(Window& window) {
    pos = 0;
    pressed = theselect = false;
    int windowWidth = window.GetWidth();
    int windowHeight = window.GetHeight();

    font->loadFromFile("../../../../../src/cassebrick/CyborgPunk.ttf");
    image->loadFromFile("../../../../../src/cassebrick/Background_Menu.png");
    bg->setTexture(*image);

    // Scale background sprite to fit the window
    float bgScaleX = (windowWidth) / 800.0f;
    float bgScaleY = (windowHeight) / 600.0f;
    bg->setScale(bgScaleX, bgScaleY);


    options = { "Blob Out", "Play", "Scores", "Options", "Quit" };
    texts.resize(options.size());

    // Set positions as percentages for dynamic resizing
    std::vector<sf::Vector2f> coords = {
        {windowWidth * 0.45625f, windowHeight * 0.0583f},  // For "Blob Out"
        {windowWidth * 0.4725f, windowHeight * 0.275f},    // For "Play"
        {windowWidth * 0.45f, windowHeight * 0.3916f},     // For "Scores"
        {windowWidth * 0.4375f, windowHeight * 0.5116f},   // For "Options"
        {windowWidth * 0.4725f, windowHeight * 0.6316f}    // For "Quit"
    };

    // Set character sizes based on window height
    std::vector<int> sizes = {
        static_cast<int>(windowHeight * 0.025),  // "Blob Out"
        static_cast<int>(windowHeight * 0.033),  // Other options
        static_cast<int>(windowHeight * 0.033),
        static_cast<int>(windowHeight * 0.033),
        static_cast<int>(windowHeight * 0.033)
    };

    for (std::size_t i = 0; i < texts.size(); ++i) {
        texts[i].setFont(*font);
        texts[i].setString(options[i]);
        texts[i].setCharacterSize(sizes[i]);
        texts[i].setOutlineColor(sf::Color::Black);
        texts[i].setPosition(coords[i]);
    }

    // Highlight "Play" by default
    texts[1].setOutlineThickness(4);
    pos = 0;

    // Scale and position the close button
    winclose->setSize(sf::Vector2f(windowWidth * 0.0475f, windowHeight * 0.0633f));
    winclose->setPosition(windowWidth * 0.90375f, windowHeight * 0.0333f);
    winclose->setFillColor(sf::Color::Transparent);

    std::vector<sf::Vector2f> collCoords = {
    {windowWidth * 0.4225f, windowHeight * 0.2516f},   // For "Play" button
    {windowWidth * 0.4225f, windowHeight * 0.3716f},   // For "Scores" button
    {windowWidth * 0.4225f, windowHeight * 0.4916f},   // For "Options" button
    {windowWidth * 0.4225f, windowHeight * 0.6116f}    // For "Quit" button
    };

    // Size of the colliders based on window dimensions
    sf::Vector2f colliderSize(windowWidth * 0.1875f, windowHeight * 0.0833f);

    // Colliders for menu buttons
    playRec->setPosition(collCoords[0]);
    scoresRec->setPosition(collCoords[1]);
    optionsRec->setPosition(collCoords[2]);
    quitRec->setPosition(collCoords[3]);

    playRec->setFillColor(sf::Color::White);
    scoresRec->setFillColor(sf::Color::White);
    optionsRec->setFillColor(sf::Color::White);
    quitRec->setFillColor(sf::Color::White);

    playRec->setSize(colliderSize);
    scoresRec->setSize(colliderSize);
    optionsRec->setSize(colliderSize);
    quitRec->setSize(colliderSize);
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

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if (winclose->getGlobalBounds().contains(mouse_coord)) {
                //std::cout << "Close the window!" << '\n';
                window.GetWindow().close();
            }
            if (playRec->getGlobalBounds().contains(mouse_coord)) {
                texts[1].setOutlineThickness(4);
                texts[pos].setOutlineThickness(0);
                pos = 1;
                gameState = 1;
            }
            if (scoresRec->getGlobalBounds().contains(mouse_coord)) {
                texts[2].setOutlineThickness(4);
                texts[pos].setOutlineThickness(0);
                pos = 2;
                gameState = 2;
            }
            if (optionsRec->getGlobalBounds().contains(mouse_coord)) {
                texts[3].setOutlineThickness(4);
                texts[pos].setOutlineThickness(0);
                pos = 3;
            }
            if (quitRec->getGlobalBounds().contains(mouse_coord)) {
                texts[4].setOutlineThickness(4);
                texts[pos].setOutlineThickness(0);
                pos = 4;
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


    window.DrawScore(fpsText);
    window.GetWindow().display();
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