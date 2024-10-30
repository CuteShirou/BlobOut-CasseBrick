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
	sprite.setPosition(pos_);
}

void Paddle::SpriteDraw(std::string imgDirectory)
{
	texture.loadFromFile(imgDirectory);
	sprite.setTexture(texture);
}

void Paddle::SetScale(float x, float y)
{
	sprite.setScale(x, y);
}

sf::Sprite Paddle::GetSprite()
{
	return sprite;
}