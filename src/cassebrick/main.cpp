#include "pch.h"
#include "main.h"
#include "Window.h"
<<<<<<< Updated upstream

#include<iostream>


int main()
{
	Window window;

	window.createWindow(800, 600);
	while (true) {
		window.pollEvents();
		std::cout << "test" << std::endl;
	}



=======
#include "Ball.h"
#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    Window window;
    sf::RenderWindow w;
    Ball ball(sf::Vector2f(100.0f, 100.0f), sf::Vector2f(1.0f, 1.0f), 5.0f);

    window.CreateWindow(800, 600);


    while (window.IsRunning()) {

        window.PollEvents();

        ball.Move();

        window.Clear();

        ball.SpriteDraw("../../../src/cassebrick/ball.");

        window.Display();
    }
>>>>>>> Stashed changes

#ifdef _DEBUG
    _CrtDumpMemoryLeaks();
#endif

    return 0;
}
