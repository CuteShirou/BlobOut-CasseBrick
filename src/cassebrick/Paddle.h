#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Entity.h"

class Paddle : public Entity
{
public:
	Paddle(sf::Vector2<float> pos);
	~Paddle();
	void Destroy() override;
	void MovePaddle(sf::Vector2f dir);
	bool OnCollision(Entity& entity) override;
	sf::Vector2<float> GetPos() override;
	void SetPos(sf::Vector2<float> pos) override;
	void SpriteDraw(std::string imgDirectory) override;
	void SetScale(float x, float y) override;
	sf::Sprite GetSprite() override;
	sf::FloatRect GetRectangle() override;

protected:
	sf::Vector2<float> pos;
	sf::Sprite sprite;
	sf::Texture texture;
};