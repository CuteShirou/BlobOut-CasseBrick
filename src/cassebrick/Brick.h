#ifndef BRICK_H__
#define BRICK_H__

#include <SFML/Graphics.hpp>
#include <vector>
#include "Entity.h"

class Brick : public Entity
{
private:
	sf::RectangleShape brick;
	bool m_IsDestroyed;
	sf::Vector2<float> posBrick;
protected :
	sf::Texture texture;
public:
	Brick(sf::Vector2<float> posBrick, sf::Vector2<float> size, sf::Color color);
	~Brick();
	void Destroy() override;
	bool IsDestroyed() const;
	bool OnCollision(Entity& entity) override;
	void Draw(sf::RenderWindow& window);
	void Move() override;
	sf::Vector2<float> GetPos() override;
	void SetPos(sf::Vector2<float> pos) override;
	sf::Sprite SpriteDraw(std::string imgDirectory) override;
};

#endif // BRICK_H__