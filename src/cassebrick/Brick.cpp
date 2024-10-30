#include "pch.h"
#include "Brick.h"

Brick::Brick(sf::Vector2<float> posBrick, sf::Vector2<float> size) : posBrick(posBrick), m_IsDestroyed(false)
{
	brick.setPosition(posBrick);
}

Brick::~Brick()
{
}

void Brick::Destroy()
{
	m_IsDestroyed = true;
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
	return brick.getPosition();
}

void Brick::SetPos(sf::Vector2<float> pos)
{
	posBrick = pos;
	brick.setPosition(pos);
}

void Brick::SpriteDraw(std::string imgDirectory)
{
	texture.loadFromFile(imgDirectory);
	brick.setTexture(texture);
}

void Brick::SetScale(float x, float y)
{
}

sf::Sprite Brick::GetSprite()
{
	return brick;
}
