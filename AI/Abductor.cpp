#include "Abductor.h"

Abductor::Abductor()
{
}


Abductor::~Abductor()
{
}

void Abductor::initialize(sf::Vector2f position, sf::Texture &texture, sf::Vector2u screenSize)
{
	GameObject::initialize(position, texture);

	_screenSize = screenSize;
}

void Abductor::update(float dt, sf::Vector2f playerPosition)
{

}

/*
void Abductor::flee(float dt)
{
	_velocity = getPosition() - _targetPosition;
	normalize(_velocity);

	move(_velocity * _speed * dt);
	_orientation = getNewOrientation(_velocity);
	setRotation(_orientation);
}
void Abductor::seek(float dt)
{
	_velocity = _targetPosition - getPosition();
	normalize(_velocity);

	move(_velocity * _speed * dt);
	_orientation = getNewOrientation(_velocity);
	setRotation(_orientation);
}

void Abductor::arrival(float dt)
{
	_velocity = _targetPosition - getPosition();
	float velocityLenght = lenght(_velocity);

	if (velocityLenght > 0)
	{
		float speed = _speed / _timeToTarget;

		if (speed > _speed)
			speed = _speed;

		normalize(_velocity);

		move(_velocity * speed * dt);
		_orientation = getNewOrientation(_velocity);
		setRotation(_orientation);
	}	
}

float Abductor::getNewOrientation(const sf::Vector2f &source)
{
	return atan2(source.y, source.x) * 180 / PI;
}

float Abductor::lenght(const sf::Vector2f &a)
{
	float lenght = sqrt((a.x * a.x) + (a.y * a.y));
	return lenght;
}

float Abductor::distance(sf::Vector2f a, sf::Vector2f b)
{
	sf::Vector2f difference = a - b;
	float distance = sqrt((difference.x * difference.x) + (difference.y * difference.y));
	
	return distance;
}

void Abductor::normalize(sf::Vector2f &source)
{
	float length = sqrt((source.x * source.x) + (source.y * source.y));

	if (length != 0 && length != 1)
		source = sf::Vector2f(source.x / length, source.y / length);
}
*/