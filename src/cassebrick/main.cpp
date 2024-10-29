#include "pch.h"
#include "main.h"
#include "Window.h"
#include "Paddle.h"
#include "Brick.h"

#include<iostream>


int main()
{
	Window window;
	Brick brick(sf::Vector2<float>(100, 100), sf::Vector2<float>(100, 100), sf::Color::Red);

	window.CreateWindow(800, 600);
	while (true) {
		window.PollEvents();
		window.Clear();
		sf::Sprite sprite = brick.SpriteDraw("../../../src/cassebrick/BRICK.png");
		window.Draw(sprite);
		window.Display();
		
	}

#ifdef _DEBUG
	_CrtDumpMemoryLeaks();
#endif

	return 0;
}