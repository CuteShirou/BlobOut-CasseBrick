#include "pch.h"
#include "Ball.h"
#include "Window.h"
#include <math.h>
#include <iostream>
#include "Ball.h"

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
  
    /*loat angle = atan2(dir.y, dir.x) * 180 / 3.14159f;
    sprite.setRotation(angle);*/

    sf::FloatRect bounds = sprite.getGlobalBounds();
    if ((pos.x <= 0 && dir.x < 0) || (pos.x + bounds.width >= window.getSize().x && dir.x > 0)) {
        dir.x = -dir.x;
    }

    if ((pos.y <= 0 && dir.y < 0) || (pos.y + bounds.height >= window.getSize().y && dir.y > 0)) {
        dir.y = -dir.y;
    }
    sprite.setPosition(pos.x, pos.y);
}

bool Ball::OnCollision(Entity& entity)
{
    sf::FloatRect ballBounds = GetRectangle();
    sf::FloatRect entityBounds = entity.GetRectangle();

    if (ballBounds.intersects(entityBounds)) {
        // Calcul de l'overlap sur chaque côté de la brique
        float overlapLeft = (entityBounds.left + entityBounds.width) - ballBounds.left;
        float overlapRight = (ballBounds.left + ballBounds.width) - entityBounds.left;
        float overlapTop = (entityBounds.top + entityBounds.height) - ballBounds.top;
        float overlapBottom = (ballBounds.top + ballBounds.height) - entityBounds.top;

        // Déterminer le côté de collision
        bool fromLeft = std::abs(overlapLeft) < std::abs(overlapRight);
        bool fromTop = std::abs(overlapTop) < std::abs(overlapBottom);

        float minOverlapX = fromLeft ? overlapLeft : overlapRight;
        float minOverlapY = fromTop ? overlapTop : overlapBottom;

        // Inverser la direction en fonction du côté touché
        if (std::abs(minOverlapX) < std::abs(minOverlapY)) {
            // Rebond sur le côté gauche ou droit, inversion de dir.x
            dir.x = -dir.x;
        }
        else {
            // Rebond sur le côté supérieur ou inférieur, inversion de dir.y
            dir.y = -dir.y;
        }

        return true; // Collision détectée et gérée
    }

    return false; // Pas de collision
}


sf::Vector2<float> Ball::GetPos()
{
    return pos;
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

sf::FloatRect Ball::GetRectangle()
{
    return sprite.getGlobalBounds();
}

void Ball::SpriteDraw(std::string imgDirectory)
{
    texture.loadFromFile(imgDirectory);
    sprite.setTexture(texture);
}


