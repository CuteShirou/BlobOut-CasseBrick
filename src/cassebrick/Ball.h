#ifndef BALL_H__
#define BALL_H__
#include "Entity.h"
#include "Window.h"

class Ball : public Entity
{
public:
	Ball(sf::Vector2<float> pos, sf::Vector2<float> dir, float speed);
	~Ball();
	void Destroy() override;
	void Move(Window&);
	bool OnCollision(Entity& entity) override;
	bool CollisionPaddle(Paddle& paddle);
	sf::Vector2<float> GetPos() override;
	void SetPos(sf::Vector2<float> pos) override;
	void SpriteDraw(std::string imgDirectory) override;
	void SetScale(float x, float y) override;
	sf::Sprite GetSprite() override;
	sf::FloatRect GetRectangle() override;
	void IncreaseSpeed(float sp);
	void SetSpeed(float sp);

protected:

	sf::Vector2<float> pos;
	sf::Vector2<float> dir;
	float speed;
	sf::Transformable transform;
	sf::Sprite sprite;
	sf::Texture texture;
};





#endif // !BALL_H__
