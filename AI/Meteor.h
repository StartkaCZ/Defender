#pragma once

#include "GameObject.h"

class Meteor : public GameObject
{
public:
					Meteor();
					~Meteor();

	void			Initialize(sf::Texture &texture, sf::FloatRect screenSize);
	void			Update(float dt);

	void			Restart();

	virtual void	CollisionEnter(GameObject*& objectCollided) override;
	void			Die();

private:
	sf::Vector2f	_velocity;
	sf::Vector2u	_screenSize;
};

