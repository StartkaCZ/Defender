#pragma once

#include "ParticleSystem.h"

#include <SFML/Graphics.hpp>

#include <map>

class ParticleSystemManager
{
public:
										ParticleSystemManager();
										~ParticleSystemManager();

	static ParticleSystemManager*		Instance();

	void								Update(float dt);
	void								Draw(sf::RenderWindow& renderWindow);

	void								AddTexture(ParticleType id, sf::Texture& texture);
	void								CreateParticleSystem(sf::Vector2f position, ParticleType type);
	void								ClearParticles();

private:
	static ParticleSystemManager*		_instance;

	std::map<ParticleType, sf::Texture> _textures;

	std::vector<ParticleSystem*>		_particleSystems;
};

