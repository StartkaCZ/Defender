#pragma once

#include "GameObject.h"

class Meteor : public GameObject
{
public:
					Meteor();
					~Meteor();

	void			Initialize(sf::Texture &texture, sf::FloatRect screenSize);
	void			Update(float dt);

	void			BorderCheck();
	void			Restart();

private:
	sf::Vector2f	_velocity;
	sf::Vector2u	_screenSize;
	sf::Vector2f	_size;
};

