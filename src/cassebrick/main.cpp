#include "pch.h"
#include "main.h"
#include "Window.h"
#include "Paddle.h"

#include<iostream>


int main()
{
	sf::Vector2f paddlePos(16.5f, 23.5f);
	Window window;
	Paddle paddle(paddlePos);

	window.CreateWindow(800, 600);
	while (true) {
		window.PollEvents();
		window.Clear();
		sf::Sprite sprite = paddle.SpriteDraw("../../../src/cassebrick/paddle.png");
		window.Draw(sprite);
		window.Display();
	}




#ifdef _DEBUG
	_CrtDumpMemoryLeaks();
#endif

	return 0;
}
