#include "pch.h"
#include "Window.h"


Window::Window()
{

}

Window::~Window()
{

}

<<<<<<< Updated upstream
void Window::createWindow(int width, int height)
=======
void Window::CreateWindow(int width, int height)
>>>>>>> Stashed changes
{

	window.create(sf::VideoMode(width, height), "*test*");
}

<<<<<<< Updated upstream
void Window::clear()
=======
void Window::Clear()
>>>>>>> Stashed changes
{
	window.clear(sf::Color::Black);
}

<<<<<<< Updated upstream
void Window::display()
=======
void Window::Display()
>>>>>>> Stashed changes
{
	window.display();
}


<<<<<<< Updated upstream
void Window::pollEvents()
=======
void Window::PollEvents()
>>>>>>> Stashed changes
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
	}
}

<<<<<<< Updated upstream
bool Window::isRunning()
=======
bool Window::IsRunning()
>>>>>>> Stashed changes
{
	return window.isOpen();
}

<<<<<<< Updated upstream
void Window::close()
{
	window.close();
}
=======
void Window::Close()
{
	window.close();
}


>>>>>>> Stashed changes
