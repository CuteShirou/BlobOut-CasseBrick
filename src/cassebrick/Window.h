#ifndef WINDOW_H__
#define WINDOW_H__

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <chrono>
#include <cstdlib> // Pour rand()
#include <ctime>   // Pour time()
#include "Paddle.h"
#include "Score.h"
#include "Particle.h"

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
	bool SetBackground(const std::string& filepath);
	void DrawParticle(ParticleSystem particle);
	sf::RenderWindow& GetWindow();
	void GetFPS();
	void ShakeWindow();
	void MoveWindow();
	void Update(int duration, int intensity);
	bool start = false;
	void BackgroundChange();

protected:
	sf::RenderWindow window;
	bool mouseControl = true;
	std::chrono::steady_clock::time_point lastKeyPressTime = std::chrono::steady_clock::now();
	float fps;
	sf::Clock clock;
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;
	sf::Clock shakeClock;
	sf::Vector2i pos;
	bool isShaking;
	std::vector<sf::Vector2i> windowRandomPos;
	int desktopWidth;
	int desktopheight;
	const std::vector<std::string> backgroundPaths = {
		"../../../src/cassebrick/Wallpaper.png",
		"../../../src/cassebrick/Wallpaper2.png",
		"../../../src/cassebrick/Wallpaper3.png",
		"../../../src/cassebrick/Wallpaper4.png"
	};
};


#endif // !WINDOW_H__