#include "pch.h"
#include "Brick.h"

Brick::Brick(sf::Vector2<float> posBrick, sf::Vector2<float> size) : posBrick(posBrick), m_IsDestroyed(false)
{
	brick.setSize(size);
	brick.setPosition(posBrick);
	brick.setFillColor(sf::Color::Red);
    Draw(SpriteDraw);
}

Brick::~Brick()
{
}

void Brick::Destroy()
{
	m_IsDestroyed = true;
	brick.setFillColor(sf::Color::Transparent);
}

bool Brick::IsDestroyed() const
{
	return m_IsDestroyed;
}

bool Brick::OnCollision(const sf::CircleShape& ball) {
    if (m_IsDestroyed) return false;

    // Coordonnées de la balle
    sf::FloatRect ballBounds = ball.getGlobalBounds();

    // Coordonnées de la brique
    sf::FloatRect brickBounds = brick.getGlobalBounds();

    // Vérifie si la balle intersecte la brique
    if (brickBounds.intersects(ballBounds)) {
        Destroy(); // Casse la brique en cas de collision
        return true;
    }
    return false;
}

void Brick::Draw(sf::RenderWindow& window)
{
	if (m_IsDestroyed)
	{
		window.draw(brick);
	}
}