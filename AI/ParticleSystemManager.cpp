#include "ParticleSystemManager.h"


ParticleSystemManager* ParticleSystemManager::_instance = nullptr;

ParticleSystemManager::ParticleSystemManager()
	: _particleSystems(std::vector<ParticleSystem*>())
{
}


ParticleSystemManager::~ParticleSystemManager()
{
	_particleSystems.clear();
}

ParticleSystemManager* ParticleSystemManager::Instance()
{
	if (_instance == nullptr)
	{
		_instance = new ParticleSystemManager();
	}

	return _instance;
}

void ParticleSystemManager::Update(float dt)
{
	for (int i = 0; i < _particleSystems.size(); i++)
	{
		if (_particleSystems[i]->isFinished())
		{
			delete _particleSystems[i];
			_particleSystems.erase(_particleSystems.begin() + i);
			i--;
		}
		else
		{
			_particleSystems[i]->Update(dt);
		}
	}
}

void ParticleSystemManager::Draw(sf::RenderWindow& renderWindow)
{
	for (int i = 0; i < _particleSystems.size(); i++)
	{
		_particleSystems[i]->Draw(renderWindow);
	}
}

void ParticleSystemManager::AddTexture(ParticleType id, sf::Texture& texture)
{
	_textures[id] = texture;
}

void ParticleSystemManager::CreateParticleSystem(sf::Vector2f position, ParticleType type)
{
	switch (type)
	{
	case ParticleSystemManager::ParticleType::PlayerLazer:
		_particleSystems.push_back(new ParticleSystem(position, _textures[type], 20));
		break;
	case ParticleSystemManager::ParticleType::EnemyLazer:
		_particleSystems.push_back(new ParticleSystem(position, _textures[type], 20));
		break;
	case ParticleSystemManager::ParticleType::Death:
		_particleSystems.push_back(new ParticleSystem(position, _textures[type], 20));
		break;
	case ParticleSystemManager::ParticleType::PowerUp:
		_particleSystems.push_back(new ParticleSystem(position, _textures[type], 20));
		break;

	default:
		break;
	}
}
