#ifndef BRICK_H__
#define BRICK_H__

#include <SFML/Graphics.hpp>
#include <vector>

class Brick
{
private:
	sf::RectangleShape brick;
	bool m_IsDestroyed;
	sf::Vector2<float> posBrick;
public:
	Brick(sf::Vector2<float> posBrick, sf::Vector2<float> size);
	~Brick();
	sf::RectangleShape GetBrick();
	void Destroy();
	bool IsDestroyed() const;
	bool CheckCollision(const sf::CircleShape& Ball);
	void Draw(sf::RenderWindow& window);
};

#endif // BRICK_H__
