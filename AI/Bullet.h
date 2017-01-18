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
				Bullet();
				~Bullet();

	void		initialize(sf::Vector2f position, sf::Texture &texture, sf::Vector2f direction, sf::Vector2u screenSize);
	void		Update(float dt);

};

