#include "Projectile.h"
#include "ConstHolder.h"


Projectile::Projectile()
{
}


Projectile::~Projectile()
{
}

void Projectile::initialize(sf::Vector2f position, sf::Texture &texture, sf::Vector2f direction, ObjectType type)
{
	GameObject::initialize(position, texture, type);

	_velocity = direction * PLAYER_LAZER_SPEED;
}

void Projectile::Update(float dt)
{
	move(_velocity * dt);
}
