#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include "Particle.h"

#include <SFML/Graphics.hpp>

#include <vector>

class ParticleSystem : protected sf::NonCopyable
{
public:
							ParticleSystem(sf::Vector2f position, sf::Texture& textures, float amount);
	void					Update(float dt);

	bool					isFinished() const;

	void					Draw(sf::RenderWindow& renderWindow);

private:
	std::vector<Particle*>	_particles;
};


#endif // !PARTICLESYSTEM_H