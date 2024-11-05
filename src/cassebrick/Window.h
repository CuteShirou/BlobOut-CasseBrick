#ifndef WINDOW_H__
#define WINDOW_H__

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <chrono>
#include "Paddle.h"
#include "Window.h"
#include "Score.h"

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
	void DrawScore(sf::Text score);
	sf::RenderWindow& GetWindow();
	void GetFPS();
	bool SetBackground(const std::string& filepath);

protected:
	sf::RenderWindow window;
	bool mouseControl = true;
	std::chrono::steady_clock::time_point lastKeyPressTime = std::chrono::steady_clock::now();
	float fps;
	sf::Clock clock;
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;
};


#endif // !WINDOW_H__