#include "pch.h"
#include <chrono>
#include "Window.h"
#include "Score.h"


Window::Window()
{
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

Window::~Window()
{

}

void Window::CreateWindow(int width, int height)
{

	desktopWidth = sf::VideoMode::getDesktopMode().width;
	desktopheight = sf::VideoMode::getDesktopMode().height;
	window.create(sf::VideoMode(width, height), "Blob Out");
	window.setVerticalSyncEnabled(true);
	pos = { (desktopWidth/2) - ((int)window.getSize().x / 2) , (desktopheight / 2) - ((int)window.getSize().y / 2) };
}

bool Window::SetBackground(const std::string& filepath) {
	if (!backgroundTexture.loadFromFile(filepath)) {
		std::cerr << "Erreur : Impossible de charger l'image de fond depuis " << filepath << std::endl;
		return false;
	}
	backgroundSprite.setTexture(backgroundTexture);
	return true;
}

void Window::Clear()
{
	window.clear(sf::Color::Black);
	window.draw(backgroundSprite);
}

void Window::Display()
{
	/*GetFPS();*/
	window.display();
}

void Window::PollEvents(Paddle* sprite) {
	sf::Event event;
	auto now = std::chrono::steady_clock::now();

	// Gestion des événements
	while (window.pollEvent(event)) {
		// Fenetre fermee
		if (event.type == sf::Event::Closed) {
			window.close();
		}

		// Touche press�e
		else if (event.type == sf::Event::KeyPressed) {
			// Desactiver le controle de la souris
			mouseControl = false;
			lastKeyPressTime = now;

			if (event.key.scancode == sf::Keyboard::Scan::Space) {
				// déclenche le move de la ball
				start = true;
			}
		}
		// Reactiver le controle par la souris apres 200 ms sans appui de touche
		if (std::chrono::duration_cast<std::chrono::milliseconds>(now - lastKeyPressTime).count() > 200) {
			mouseControl = true;
		}

		// Deplacement par la souris uniquement si le controle par la souris est actif
		if (mouseControl) {
			sf::Vector2i mouse = sf::Mouse::getPosition(window);
			sprite->SetPos(sf::Vector2f(window.mapPixelToCoords(mouse).x - sprite->GetSprite().getGlobalBounds().width / 2, 500));
			if (sprite->GetPos().x + sprite->GetSprite().getGlobalBounds().width >= window.getSize().x) {
				sprite->SetPos(sf::Vector2f(window.getSize().x - sprite->GetSprite().getGlobalBounds().width, 500));
			}
			if (sprite->GetPos().x <= 0) {
				sprite->SetPos(sf::Vector2f(0, 500));
			}
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

void Window::DrawScore(sf::Text score)
{
	window.draw(score);
}

void Window::DrawParticle(ParticleSystem particle)
{
	window.draw(particle);
}

sf::RenderWindow& Window::GetWindow()
{
	return window;
}

void Window::GetFPS()
{
	fps = 1.0f / clock.getElapsedTime().asSeconds();

	std::cout << "FPS: " << fps << std::endl;

	clock.restart();
}

void Window::ShakeWindow()
{
	shakeClock.restart(); // Redémarrer le chronomètre
	isShaking = true; // Indiquer que le tremblement est actif
}

void Window::MoveWindow()
{
	int x = (rand() % (desktopWidth - (int)window.getSize().x));
	int y = (rand() % (desktopheight - (int)window.getSize().y));
	window.setPosition({ x, y });
	pos = window.getPosition();
}


void Window::Update(int duration, int intensity)
{
	if (isShaking) {
		// Vérifie si la durée du tremblement est écoulée
		if (shakeClock.getElapsedTime().asMilliseconds() < duration) { // Utilisez duration ici
			// Calcul des décalages aléatoires
			int offsetX = (rand() % (intensity * 2)) - intensity; // Valeurs entre -intensity et intensity
			int offsetY = (rand() % (intensity * 2)) - intensity; // Valeurs entre -intensity et intensity
			// Déplace la fenêtre
			window.setPosition({ pos.x + offsetX, pos.y + offsetY });
		}
		else {
			// Remet la fenêtre à sa position d'origine
			window.setPosition(pos);
			isShaking = false; // Arrête le tremblement
		}
	}
}

void Window::BackgroundChange() {
	int index = std::rand() % backgroundPaths.size();
	if (!SetBackground(backgroundPaths[index])) {
		std::cerr << "Erreur lors du chargement du fond d'écran aléatoire." << std::endl;
	}
}