#include "Meteor.h"
#include "ConstHolder.h"

#include "ParticleSystemManager.h"
#include "AudioManager.h"

Meteor::Meteor()
{
}


Meteor::~Meteor()
{
}

void Meteor::Initialize(sf::Texture &texture, sf::FloatRect screenSize)
{
	sf::Vector2f position = sf::Vector2f(0,0);
	GameObject::initialize(position, texture, ObjectType::Obstacle_Meteor);

	_screenSize = sf::Vector2u(screenSize.width, screenSize.height);

	Restart();
}

void Meteor::Update(float dt)
{
	move(_velocity * dt);

	if (getPosition().y > _screenSize.y)
	{
		Restart();
	}
}

void Meteor::Restart()
{
	float x = rand() % (int)(_screenSize.x - _size.x - _size.x - _size.x - _size.x) + _size.x + _size.x;
	float y = -rand() % (int)(_size.y + _size.y) - _size.y;

	setPosition(x, y);

	_velocity = sf::Vector2f(((rand() % 20 - 10)* 0.1f), (rand() % 5 + 6) * 0.1f) * METEOR_FALL_SPEED;

	setRotation(std::atan2(_velocity.y, _velocity.x) * 180 / PI);

	_isAlive = true;
}

void Meteor::CollisionEnter(GameObject*& objectCollided)
{
	if (//objectCollided->getType() == ObjectType::Projetile_Interceptor || objectCollided->getType() == ObjectType::Projetile_PlayerLazer || 
		objectCollided->getType() == ObjectType::Player ||
		objectCollided->getType() == ObjectType::Abductor || objectCollided->getType() == ObjectType::AlienNest || objectCollided->getType() == ObjectType::Mutant)
	{
		Die();
		AudioManager::Instance()->PlaySound(AudioManager::SoundType::UnitDestroyed);
		ParticleSystemManager::Instance()->CreateParticleSystem(getPosition(), ParticleSystemManager::ParticleType::Death);
	}
	else if (objectCollided->getType() == ObjectType::Projetile_Interceptor || objectCollided->getType() == ObjectType::Projetile_PlayerLazer)
	{
		AudioManager::Instance()->PlaySound(AudioManager::SoundType::UnitHit);
		ParticleSystemManager::Instance()->CreateParticleSystem((getPosition() + objectCollided->getPosition()) * 0.5f, ParticleSystemManager::ParticleType::EnemyLazer);
	}
}

void Meteor::Die()
{
	_isAlive = false;
}

bool Meteor::getAlive() const
{
	return _isAlive;
}
