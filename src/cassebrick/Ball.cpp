#include "pch.h"
#include "Ball.h"
#include "Window.h"
#include <math.h>

Ball::Ball(sf::Vector2<float> pos_, sf::Vector2<float> dir_, float speed_) : pos(pos_), dir(dir_), speed(speed_)
{
}

Ball::~Ball()
{
}

void Ball::Destroy()
{
}

void Ball::Move(Window& w)
{
    sf::RenderWindow& window = w.GetWindow();
    pos.x += dir.x * speed;
    pos.y += dir.y * speed;
    sprite.setPosition(pos.x, pos.y);

    float angle = atan2(dir.y, dir.x) * 180 / 3.14159f;
    sprite.setRotation(angle);

    sf::FloatRect bounds = sprite.getGlobalBounds();
    if ((pos.x <= 0 && dir.x < 0) || (pos.x + bounds.width >= window.getSize().x && dir.x > 0)) {
        dir.x = -dir.x;
    }

    if ((pos.y <= 0 && dir.y < 0) || (pos.y + bounds.height >= window.getSize().y && dir.y > 0)) {
        dir.y = -dir.y;
    }
}

bool Ball::OnCollision(Entity& entity)
{
    sf::FloatRect ballBounds = GetRectangle();
    sf::FloatRect entityBounds = entity.GetRectangle();

    if ((ballBounds.left < entityBounds.left && ballBounds.left + ballBounds.width > entityBounds.left) ||
        (ballBounds.left + ballBounds.width > entityBounds.left + entityBounds.width && ballBounds.left < entityBounds.left + entityBounds.width))
    {
        dir.x = -dir.x;
        return true;
    }

    if ((ballBounds.top < entityBounds.top && ballBounds.top + ballBounds.height > entityBounds.top) ||
        (ballBounds.top + ballBounds.height > entityBounds.top + entityBounds.height && ballBounds.top < entityBounds.top + entityBounds.height))
    {
        dir.y = -dir.y;
        return true;
    }

    return false;
}


sf::Vector2<float> Ball::GetPos()
{
    return sf::Vector2<float>();
}

void Ball::SetPos(sf::Vector2<float> pos)
{
    sprite.setPosition(pos);
}

void Ball::SetScale(float x, float y)
{
    sprite.setScale(x, y);
}

sf::Sprite Ball::GetSprite()
{
    return sprite;
}

void Ball::SpriteDraw(std::string imgDirectory)
{
    sprite.setTexture(texture);
    sprite.setPosition(pos);
}

