#ifndef BRICK_H__
#define BRICK_H__

#include <SFML/Graphics.hpp>
#include <vector>
#include "Entity.h"

class Brick : public Entity
{
protected :
	sf::Sprite brick;
	sf::Texture texture;
	bool m_IsDestroyed;
	sf::Vector2<float> posBrick;
public:
	Brick(sf::Vector2<float> posBrick, sf::Vector2<float> size);
	~Brick();
	void Destroy() override;
	bool IsDestroyed() const;
	bool OnCollision(Entity& entity) override;
	void Draw(sf::RenderWindow& window);
	void Move() override;
	sf::Vector2<float> GetPos() override;
	void SetPos(sf::Vector2<float> pos) override;
	void SpriteDraw(std::string imgDirectory) override;
	void SetScale(float x, float y) override;
	sf::Sprite GetSprite() override;
};

#endif // BRICK_H__