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


void Window::PollEvents()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
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


