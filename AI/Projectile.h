#pragma once

#include "GameObject.h"

class Projectile : public GameObject
{
public:
					Projectile();
					~Projectile();

	void			initialize(sf::Vector2f position, sf::Texture &texture, sf::Vector2f direction, ObjectType type);


	void			Update(float dt);

private:
	sf::Vector2f	_velocity;
};

