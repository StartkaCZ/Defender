#pragma once

#include "GameObject.h"

class Projectile : public GameObject
{
public:
					Projectile();
					~Projectile();

	void			initialize(sf::Vector2f position, sf::Texture &texture, sf::Vector2f direction, sf::Vector2u screenSize, ObjectType type, float timeToLive);
	void			Update(float dt);

	virtual void	CollisionEnter(GameObject*& objectCollided) override;
	virtual void	Die();

protected:
	sf::Vector2f	_velocity;
	sf::Vector2u	_screenSize;

	float			_timeToLive;
};

