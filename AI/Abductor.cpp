#include "Abductor.h"

Abductor::Abductor()
{
}


Abductor::~Abductor()
{
}

void Abductor::Initialize(sf::Vector2f position, sf::Texture &texture, sf::FloatRect screenSize)
{
	GameObject::initialize(position, texture, ObjectType::Abductor);

	_screenSize = sf::Vector2u(screenSize.width, screenSize.height);
}

void Abductor::Update(float dt, sf::Vector2f playerPosition)
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
*/