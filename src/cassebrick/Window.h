#ifndef WINDOW_H__
#define WINDOW_H__

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Paddle.h"

class Window
{
public:
	Window();
	~Window();
	void CreateWindow(int width, int height);
	void Clear(); 
	void Display();
	void PollEvents(Paddle* sprite);
	bool IsRunning();
	void Close();
	void Draw(sf::Sprite sprite);
	

protected:
	sf::RenderWindow window;

};


#endif // !WINDOW_H__
