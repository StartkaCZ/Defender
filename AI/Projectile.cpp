#include "Projectile.h"
#include "ConstHolder.h"


Projectile::Projectile()
{
}


Projectile::~Projectile()
{
}

void Projectile::initialize(sf::Vector2f position, sf::Texture &texture, sf::Vector2f direction, sf::Vector2u screenSize, ObjectType type)
{
	GameObject::initialize(position, texture, type);

	_screenSize = screenSize;
	_velocity = direction * PLAYER_LAZER_SPEED;

	_isAlive = true;
}

void Projectile::Update(float dt)
{
	move(_velocity * dt);

	BorderCheck();
}

void Projectile::BorderCheck()
{
	if (getPosition().x + _size.x < 0 || getPosition().x - _size.x > _screenSize.x ||
		getPosition().y - _size.y > _screenSize.y)
	{
		Die();
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
