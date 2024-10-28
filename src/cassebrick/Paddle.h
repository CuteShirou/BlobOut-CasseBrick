#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include <iostream>

class Paddle : public Entity
{
public:
	Paddle(sf::Vector2<float> pos);
	~Paddle();
	void Destroy() override;
	void Move() override;
	bool OnCollision(Entity& entity) override;
	sf::Vector2<float> GetPos() override;
	void SetPos(sf::Vector2<float> pos) override;
	sf::Sprite SpriteDraw(std::string imgDirectory) override;

protected:
	sf::Vector2<float> pos;
	sf::Sprite sprite;
};
