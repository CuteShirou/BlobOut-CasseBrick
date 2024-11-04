#ifndef WINDOW_H__
#define WINDOW_H__

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <chrono>
#include "Paddle.h"
#include "Window.h"
#include "Particle.h"
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
	void DrawParticle(ParticleSystem particle);
	sf::RenderWindow& GetWindow();
	void GetFPS();

protected:
	sf::RenderWindow window;
	bool mouseControl = true;
	std::chrono::steady_clock::time_point lastKeyPressTime = std::chrono::steady_clock::now();
	float fps;
	sf::Clock clock;
};


#endif // !WINDOW_H__