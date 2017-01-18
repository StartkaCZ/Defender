#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include "Particle.h"

#include <SFML/Graphics.hpp>

#include <vector>

enum class ParticleType
{
	PlayerLazer,
	EnemyLazer,
	Death,
	PowerUp,
	PlayerTrail,
};

class ParticleSystem : protected sf::NonCopyable
{
public:
							ParticleSystem(sf::Vector2f position, sf::Texture& texture, float amount, ParticleType particleType);
	void					CreatePlayerLazerParticles(sf::Vector2f position, float amount, sf::Texture& texture);
	void					CreateEnemyLazerParticles(sf::Vector2f position, float amount, sf::Texture& texture);
	void					CreateDeathParticles(sf::Vector2f position, float amount, sf::Texture& texture);
	void					CreatePowerUpParticles(sf::Vector2f position, float amount, sf::Texture& texture);
	void					CreatePlayerTrailParticles(sf::Vector2f position, float amount, sf::Texture& texture);

	void					Update(float dt);

	bool					isFinished() const;

	void					Draw(sf::RenderWindow& renderWindow);

private:
	std::vector<Particle*>	_particles;
};


#endif // !PARTICLESYSTEM_H