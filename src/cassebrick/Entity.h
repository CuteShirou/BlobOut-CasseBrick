#ifndef ENTITY_H__
#define ENTITY_H__

#include <iostream>
#include <vector>
#include "Window.h"
#include <SFML/Graphics.hpp>

class Entity
{
public:
	Entity(sf::Vector2<float> pos);
	~Entity();
	virtual void Destroy() = 0;
	virtual void Move(Window&) = 0;
	virtual bool OnCollision(Entity& entity) = 0;
	virtual sf::Vector2<float> GetPos() = 0;
	virtual void SpriteDraw(std::string imgDirectory) = 0;
	virtual void SetPos(sf::Vector2<float> pos) = 0;
	virtual void SetScale(float x, float y) = 0;
	virtual sf::Sprite GetSprite() = 0;
	virtual sf::FloatRect GetRectangle() = 0;


	sf::FloatRect GetRectangle() const {
		return sprite.getGlobalBounds();
	}


protected:
	sf::Vector2<float> pos;
	sf::Sprite sprite;

};


#endif // !ENTITY_H__

