#include "Meteor.h"
#include "ConstHolder.h"


Meteor::Meteor()
{
}


Meteor::~Meteor()
{
}

void Meteor::Initialize(sf::Texture &texture, sf::FloatRect screenSize)
{
	sf::Vector2f position = sf::Vector2f(0,0);
	GameObject::initialize(position, texture, ObjectType::Obstacle_Meteor);

	_screenSize = sf::Vector2u(screenSize.width, screenSize.height);

	Restart();
}

void Meteor::Update(float dt)
{
	move(_velocity * dt);

	BorderCheck();
}

void Meteor::BorderCheck()
{
	if (getPosition().x + _size.x < 0 || getPosition().x - _size.x > _screenSize.x ||
		getPosition().y - _size.y > _screenSize.y)
	{
		Restart();
	}
}

void Meteor::Restart()
{
	float x = (rand() % _screenSize.x - _size.x - _size.x) + _size.x;
	float y = -rand() % (int)_size.y - _size.y - _size.y;

	setPosition(x, y);

	_velocity = sf::Vector2f(((rand() % 20 - 10)* 0.1f), (rand() % 5 + 6) * 0.1f) * METEOR_FALL_SPEED;

	setRotation(std::atan2(_velocity.y, _velocity.x) * 180 / PI);

	_isAlive = true;
}

void Meteor::Die()
{
	_isAlive = false;
}

bool Meteor::getAlive() const
{
	return _isAlive;
}
