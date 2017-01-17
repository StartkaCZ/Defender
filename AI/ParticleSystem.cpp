#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(sf::Vector2f position, sf::Texture& texture, float amount)
{
	for (int i = 0; i < amount; i++)
	{
		_particles.push_back(
			new Particle( rand() % 1 + 1
						, sf::Vector2f((float)(rand() % 21 - 10), (float)(rand() % 21 - 10))
						, rand() % 25 + 25
						, position
						, texture));
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