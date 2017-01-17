#include "Projectile.h"
#include "ConstHolder.h"


Projectile::Projectile()
{
}


Projectile::~Projectile()
{
}

void Projectile::initialize(sf::Vector2f position, sf::Texture &texture, sf::Vector2f direction, sf::Vector2u screenSize, ObjectType type, float timeToLive)
{
	GameObject::initialize(position, texture, type);

	_screenSize = screenSize;
	_velocity = direction * PLAYER_LAZER_SPEED;

	setRotation(std::atan2(_velocity.y, _velocity.x) * 180 / PI);

	_timeToLive = timeToLive;

	_isAlive = true;
}

void Projectile::Update(float dt)
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

void Projectile::CollisionEnter(GameObject*& objectCollided)
{
	if (_type == ObjectType::Projetile_PlayerLazer)
	{
		if (objectCollided->getType() == ObjectType::Abductor || objectCollided->getType() == ObjectType::AlienNest || objectCollided->getType() == ObjectType::Mutant)
		{
			Die();
		}
	}
	else
	{
		if (objectCollided->getType() == ObjectType::Player)
		{
			Die();
		}
	}
}

void Projectile::Die()
{
	_isAlive = false;
}

bool Projectile::getAlive() const
{
	return _isAlive;
}
