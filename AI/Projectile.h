#pragma once

#include "GameObject.h"

class Projectile : public GameObject
{
public:
					Projectile();
					~Projectile();

	void			initialize(sf::Vector2f position, sf::Texture &texture, sf::Vector2f direction, sf::Vector2u screenSize, ObjectType type);
	void			Update(float dt);

	virtual void	Die();

	bool			getAlive() const;

protected:
	void			BorderCheck();

protected:
	sf::Vector2f	_velocity;
	sf::Vector2u	_screenSize;

	bool			_isAlive;
};

