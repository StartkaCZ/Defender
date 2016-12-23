#include "Interceptor.h"
#include "ConstHolder.h"
#include "Vector2Calculator.h"

Interceptor::Interceptor(int& parentRocketCounter)
	: _parentRocketCounter(parentRocketCounter)
	, _timeToLive(NEST_INTERCEPTOR_MISSILE_LIFE_TIME)
{
}

Interceptor::~Interceptor()
{
}

void Interceptor::initialize(sf::Vector2f position, sf::Texture &texture, sf::Vector2f target, sf::Vector2u screenSize)
{
	sf::Vector2f direction = target - getPosition();
	
	Vector2Calculator::Normalize(direction);

	Projectile::initialize(position, texture, direction, screenSize, ObjectType::Projetile_Interceptor);
}

void Interceptor::Update(float dt, sf::Vector2f playerPosition)
{
	if (_timeToLive > 0)
	{
		_timeToLive -= dt;

		move(_velocity * dt);

		CalculateVelocity(playerPosition);
	}
	else
	{
		Die();
	}
}
void Interceptor::CalculateVelocity(sf::Vector2f playerPosition)
{
	sf::Vector2f target = playerPosition - getPosition();

	Vector2Calculator::Normalize(target);

	_velocity = target * NEST_INTERCEPTOR_MISSILE_MAX_SPEED;
}

void Interceptor::Die()
{
	Projectile::Die();
	
	_parentRocketCounter--;
}