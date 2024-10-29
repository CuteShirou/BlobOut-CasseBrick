#include "pch.h"
#include "Window.h"


Window::Window()
{

}

Window::~Window()
{

}

void Window::CreateWindow(int width, int height)
{

	window.create(sf::VideoMode(width, height), "*test*");
}

void Window::Clear()
{
	window.clear(sf::Color::Black);
}

void Window::Display()
{
	window.display();
}


void Window::PollEvents(Paddle* sprite)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed) {
			window.close();
		}
		else if (event.type == sf::Event::KeyPressed) {
			std::cout << "Key Pressed" << std::endl;
			if (event.key.scancode == sf::Keyboard::Scan::A) {
				std::cout << "Key Q Pressed" << std::endl;
				// if (!0 == sprite.GetPos().x) {
					sprite->MovePaddle(sf::Vector2f(10, 0));
					std::cout << "Moving Left" << std::endl;
					std::cout << sprite->GetPos().x << std::endl;
				// }
			}
			else if (event.key.scancode == sf::Keyboard::Scan::D) {
				std::cout << "Key D Pressed" << std::endl;
				// if (!window.getSize().x == sprite.GetPos().x + sprite.GetSprite().getGlobalBounds().width) {
					sprite->MovePaddle(sf::Vector2f(-10, 0));
					std::cout << "Moving Right" << std::endl;
				// }
			}
		}
	}
}

bool Window::IsRunning()
{
	return window.isOpen();
}

void Window::Close()
{
	window.close();
}

void Window::Draw(sf::Sprite sprite)
{
	window.draw(sprite);
}
