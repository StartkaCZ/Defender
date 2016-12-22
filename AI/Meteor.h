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

	void			Die();

	bool			getAlive() const;

private:
	void			BorderCheck();

private:
	sf::Vector2f	_velocity;
	sf::Vector2u	_screenSize;

	bool			_isAlive;
};

