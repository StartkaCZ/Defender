#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(sf::Vector2f position, sf::Texture& texture, float amount, ParticleType particleType)
{
	switch (particleType)
	{
	case ParticleType::PlayerLazer:
		CreatePlayerLazerParticles(position, amount, texture);
		break;
	case ParticleType::EnemyLazer:
		CreateEnemyLazerParticles(position, amount, texture);
		break;
	case ParticleType::Death:
		CreateDeathParticles(position, amount, texture);
		break;
	case ParticleType::PowerUp:
		CreatePowerUpParticles(position, amount, texture);
		break;
	case ParticleType::PlayerTrail:
		CreatePlayerTrailParticles(position, amount, texture);
		break;

	default:
		break;
	}
}
void ParticleSystem::CreatePlayerLazerParticles(sf::Vector2f position, float amount, sf::Texture& texture)
{
	for (int i = 0; i < amount; i++)
	{
		_particles.push_back(new Particle((rand() % 5 + 5) * 0.1f, sf::Vector2f((float)(rand() % 21 - 10), (float)(rand() % 21 - 10)), rand() % 10 + 5, 255, position, texture));
	}
}
void ParticleSystem::CreateEnemyLazerParticles(sf::Vector2f position, float amount, sf::Texture& texture)
{
	for (int i = 0; i < amount; i++)
	{
		_particles.push_back(new Particle((rand() % 5 + 5) * 0.1f, sf::Vector2f((float)(rand() % 21 - 10), (float)(rand() % 21 - 10)), rand() % 10 + 5, 255, position, texture));
	}
}
void ParticleSystem::CreateDeathParticles(sf::Vector2f position, float amount, sf::Texture& texture)
{
	for (int i = 0; i < amount; i++)
	{
		_particles.push_back(new Particle((rand() % 5 + 5) * 0.1f, sf::Vector2f((float)(rand() % 21 - 10), (float)(rand() % 21 - 10)), rand() % 10 + 5, 255, position, texture));
	}
}
void ParticleSystem::CreatePowerUpParticles(sf::Vector2f position, float amount, sf::Texture& texture)
{
	for (int i = 0; i < amount; i++)
	{
		_particles.push_back(new Particle((rand() % 5 + 5) * 0.1f, sf::Vector2f((float)(rand() % 21 - 10), (float)(rand() % 21 - 10)), rand() % 10 + 5, 255, position, texture));
	}
}
void ParticleSystem::CreatePlayerTrailParticles(sf::Vector2f position, float amount, sf::Texture& texture)
{
	for (int i = 0; i < amount; i++)
	{
		_particles.push_back(new Particle((rand() % 5 + 2) * 0.1f, sf::Vector2f((float)(rand() % 21 - 10), (float)(rand() % 21 - 10)), rand() % 5 + 5, 255, position, texture));
	}
}

void ParticleSystem::Update(float dt)
{
	for (int i = 0; i < _particles.size(); i++)
	{
		if (_particles.at(i)->isAlive())
		{
			_particles.at(i)->Update(dt);
		}
		else
		{
			delete _particles[i];
			_particles.erase(_particles.begin() + i);
			i--;
		}
	}
}

void ParticleSystem::Draw(sf::RenderWindow& renderWindow)
{
	for (int i = 0; i < _particles.size(); i++)
	{
		if (_particles[i]->isAlive())
		{
			renderWindow.draw(*_particles[i]);
		}
	}
}

bool ParticleSystem::isFinished() const
{
	return  _particles.size() == 0;
}