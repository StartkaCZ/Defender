#include "Bullet.h"

Bullet::Bullet() : _velocity(sf::Vector2f()), _timeToLive(ABDUCTOR_BULLET_LIFE_TIME)
{

};

Bullet::~Bullet()
{

}

void Bullet::initialize(sf::Vector2f position, sf::Texture &texture, sf::Vector2f direction, sf::Vector2u screenSize)
{
	_velocity = direction * ADBUCTOR_BULLET_SPEED;
	Projectile::initialize(position, texture, direction, screenSize, ObjectType::Projetile_Bullet, 5.0f);
}

void Bullet::Update(float dt)
{
	if (_timeToLive > 0 && getPosition().y < _screenSize.y * PLAYER_OFFSET_FROM_GROUND + _size.y)
	{
		_timeToLive -= dt;

		move(_velocity * dt);
	}
	else
	{
		Die();
	}
}


