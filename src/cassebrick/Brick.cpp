#include "pch.h"
#include "Brick.h"

Brick::Brick(sf::Vector2<float> posBrick, sf::Vector2<float> size, sf::Color color) : posBrick(posBrick), m_IsDestroyed(false)
{
	brick.setSize(size);
	brick.setPosition(posBrick);
	brick.setFillColor(color);
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

bool Brick::OnCollision(Entity& entity)
{
	return false;
}

void Brick::Draw(sf::RenderWindow& window)
{
	if (!m_IsDestroyed)
	{
		window.draw(brick);
	}
}

void Brick::Move()
{
}

sf::Vector2<float> Brick::GetPos()
{
	return sf::Vector2<float>();
}

void Brick::SetPos(sf::Vector2<float> pos)
{
}

sf::Sprite Brick::SpriteDraw(std::string imgDirectory)
{
	texture.loadFromFile(imgDirectory);
	sf::Sprite sprite(texture);
	return sprite;
}