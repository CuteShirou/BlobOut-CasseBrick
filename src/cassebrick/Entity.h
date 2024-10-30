#ifndef ENTITY_H__
#define ENTITY_H__

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

class Entity
{
public:
	Entity();
	~Entity();
	virtual void Destroy() = 0;
	virtual void Move() = 0;
	virtual bool OnCollision(Entity& entity) = 0;
	virtual sf::Vector2<float> GetPos() = 0;
	virtual void SetPos(sf::Vector2<float> pos) = 0;
	virtual void SpriteDraw(std::string imgDirectory) = 0;
	virtual void SetScale(float x, float y) = 0;
	virtual sf::Sprite GetSprite() = 0;
protected:
	sf::Vector2<float> pos;

};


#endif // !ENTITY_H__