#include "pch.h"
#include "Window.h"


Window::Window()
{

}

Window::~Window()
{

}

void Window::createWindow(int width, int height)
{

	window.create(sf::VideoMode(width, height), "*test*");
}

void Window::clear()
{
	window.clear(sf::Color::Black);
}

void Window::display()
{
	window.display();
}


void Window::pollEvents()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
	}
}

bool Window::isRunning()
{
	return window.isOpen();
}

void Window::close()
{
	window.close();
}
