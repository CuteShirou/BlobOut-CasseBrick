#include "pch.h"
#include <SFML/Graphics.hpp>
#include "Paddle.h"

Paddle::Paddle(sf::Vector2<float> pos_) : pos(pos_)
{
	sprite.setPosition(pos);
}

Paddle::~Paddle()
{
}

void Paddle::Destroy()
{
}

void Paddle::MovePaddle(sf::Vector2f dir)
{
	sprite.move(dir);

}

bool Paddle::OnCollision(Entity& entity)
{
	return false;
}

sf::Vector2<float> Paddle::GetPos()
{
	return sprite.getPosition();
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

sf::FloatRect Paddle::GetRectangle()
{
	return sprite.getGlobalBounds();
}