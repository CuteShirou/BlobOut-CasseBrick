#include "pch.h"
#include "main.h"
#include "Window.h"
#include "Paddle.h"

#include<iostream>


int main()
{
	sf::Vector2f paddlePos(350, 500);
	Window window;
	Paddle paddle(paddlePos);

	window.CreateWindow(800, 600);
	while (true) {
		window.Clear();

		window.PollEvents();

		paddle.SetPos(paddlePos);
		paddle.SpriteDraw("../../../src/cassebrick/paddle.png");
		paddle.SetScale(1, 1.2);
		window.Draw(paddle.GetSprite());

		window.Display();
	}




#ifdef _DEBUG
	_CrtDumpMemoryLeaks();
#endif

	return 0;
}
