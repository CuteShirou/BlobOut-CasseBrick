#include "pch.h"
#include "Window.h"
#include <chrono>


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

void Window::PollEvents(Paddle* sprite) {
	sf::Event event;
	auto now = std::chrono::steady_clock::now();

	// Gestion des �v�nements
	while (window.pollEvent(event)) {
		// Fen�tre ferm�e
		if (event.type == sf::Event::Closed) {
			window.close();
		}

		// Touche press�e
		else if (event.type == sf::Event::KeyPressed) {
			// D�sactiver le contr�le de la souris
			mouseControl = false;
			lastKeyPressTime = now;

			// Touche A
			if (event.key.scancode == sf::Keyboard::Scan::A) {
				// Si le paddle est dans la fen�tre, il peut bouger
				if (sprite->GetSprite().getPosition().x > 0) {
					sprite->MovePaddle(sf::Vector2f(-8, 0));
					// S'il d�passe la fen�tre d� � sa vitesse, le t�l�porte � la bordure 
					if (sprite->GetPos().x <= 0) {
						sprite->SetPos(sf::Vector2f(0, 500));
					}
				}
			}
			// Touche D
			else if (event.key.scancode == sf::Keyboard::Scan::D) {
				// Si le paddle est dans la fen�tre, il peut bouger
				if (window.getSize().x > sprite->GetPos().x + sprite->GetSprite().getGlobalBounds().width) {
					sprite->MovePaddle(sf::Vector2f(10, 0));
					// S'il d�passe la fen�tre d� � sa vitesse, le t�l�porte � la bordure 
					if (sprite->GetPos().x + sprite->GetSprite().getGlobalBounds().width >= window.getSize().x) {
						sprite->SetPos(sf::Vector2f(window.getSize().x - sprite->GetSprite().getGlobalBounds().width, 500));
					}
				}
			}
		}
		// R�activer le contr�le par la souris apr�s 200 ms sans appui de touche
		if (std::chrono::duration_cast<std::chrono::milliseconds>(now - lastKeyPressTime).count() > 200) {
			mouseControl = true;
		}

		// D�placement par la souris uniquement si le contr�le par la souris est actif
		if (mouseControl) {
			sf::Vector2i mouse = sf::Mouse::getPosition(window);
			sprite->SetPos(sf::Vector2f(window.mapPixelToCoords(mouse).x - sprite->GetSprite().getGlobalBounds().width / 2, 500));
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

sf::RenderWindow& Window::GetWindow()
{
	return window;
}
