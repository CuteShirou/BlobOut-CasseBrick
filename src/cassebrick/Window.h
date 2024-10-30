#ifndef WINDOW_H__
#define WINDOW_H__

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Window
{
public:
	Window();
	~Window();
	void CreateWindow(int width, int height);
	void Clear();
	void Display();
	void PollEvents();
	bool IsRunning();
	void Close();
	sf::RenderWindow& GetWindow();

protected:
	sf::RenderWindow window;

};


#endif // !WINDOW_H__
