#ifndef WINDOW_H__
#define WINDOW_H__

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Window
{
public:
	Window();
	~Window();
	virtual void createWindow(int width, int height);
	void clear(); 
	virtual void display();
	virtual void pollEvents();
	virtual bool isRunning();
	virtual void close();
	void CreateWindow(int width, int height);
	void Clear();
	void Display();
	void PollEvents();
	bool IsRunning();
	void Close();

protected:
	sf::RenderWindow window;

};


#endif // !WINDOW_H__
