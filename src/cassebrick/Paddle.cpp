#include "pch.h"
#include "Paddle.h"
#include <SFML/Graphics.hpp>

Paddle::Paddle(sf::Vector2<float> pos_) : pos(pos_)
{
}

Paddle::~Paddle()
{
}

void Paddle::Destroy()
{
}

void Paddle::Move()
{
}

bool Paddle::OnCollision(Entity& entity)
{
	return false;
}

sf::Vector2<float> Paddle::GetPos()
{
	return pos;
}

void Paddle::SetPos(sf::Vector2<float> pos_)
{
	pos = pos_;
}

sf::Sprite Paddle::SpriteDraw(std::string imgDirectory)
{
	sf::Texture texture;
	texture.loadFromFile(imgDirectory);
	sf::Sprite sprite(texture);
	return sprite;
}
