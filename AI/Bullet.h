#pragma once
#include "Projectile.h"
#include "ConstHolder.h"
#include "Vector2Calculator.h"
class Bullet : public Projectile
{
private:
	sf::Vector2f _velocity;
	float	_timeToLive;
public:
	Bullet() : _velocity(sf::Vector2f()),_timeToLive(ABDUCTOR_BULLET_LIFE_TIME)
	{

	};
	~Bullet()
	{

	}

	void initialize(sf::Vector2f position, sf::Texture &texture, sf::Vector2f target, sf::Vector2u screenSize)
	{
		sf::Vector2f direction = target - position;
		Vector2Calculator::Normalize(direction);
		_velocity = direction * ADBUCTOR_BULLET_SPEED;
		Projectile::initialize(position, texture, direction, screenSize, ObjectType::Projetile_Bullet);
	}

	void Update(float dt)
	{
		if (_timeToLive > 0)
		{
			_timeToLive -= dt;

			move(_velocity * dt);
		}
		else
		{
			Die();
		}
	}
};
