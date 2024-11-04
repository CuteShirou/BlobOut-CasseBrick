#ifndef PARTICLE_H__
#define PARTICLE_H__
#include <SFML/Graphics.hpp>
#include "Ball.h"

class ParticleSystem : public sf::Drawable, public sf::Transformable
{
public:
	ParticleSystem(unsigned int count) :
		m_particles(count),
		m_vertices(sf::Points, count),
		m_lifetime(sf::seconds(3.f)),
		m_emitter(0.f, 0.f)
	{
	};
	void SetEmitter(sf::Vector2f position);
	void Update(sf::Time elapsed);

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	struct Particle
	{
		sf::Vector2f velocity;
		sf::Time lifetime;
	};
	void resetParticle(std::size_t index);
	std::vector<Particle> m_particles;
	sf::VertexArray m_vertices;
	sf::Time m_lifetime;
	sf::Vector2f m_emitter;
};

#endif