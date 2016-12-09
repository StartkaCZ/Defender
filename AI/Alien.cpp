#include "Alien.h"


void Alien::initialize(sf::Vector2f position, sf::Texture &texture, sf::Vector2u screenSize, bool flee)
{
	_sprite = sf::Sprite();
	_sprite.setTexture(texture);
	setPosition(position);

	_speed = SPEED;
	_screenSize = screenSize;

	_velocity = sf::Vector2f(rand() % 3 - 1, rand() % 3 - 1);

	while (_velocity.x == 0 && _velocity.y == 0)
	{
		_velocity = sf::Vector2f(rand() % 3 - 1, rand() % 3 - 1);
	}

	_flee = flee;

	_sprite.setOrigin(texture.getSize().x * 0.5f, texture.getSize().y * 0.5f);
	_orientation = atan2(_velocity.y, _velocity.x) * 180 / PI;
	_velocity = sf::Vector2f(cos(_orientation * PI / 180), sin(_orientation * PI / 180));
	setRotation(_orientation);
}

void Alien::update(float dt, sf::Vector2f playerPosition)
{
	_timeToTarget = distance(playerPosition, getPosition()) / _speed * dt;
	_targetPosition = playerPosition;

	if (_flee)
	{
		if (distance(getPosition(), playerPosition) > (_screenSize.x + _screenSize.y) / 8.f)
			seek(dt);
		else
			flee(dt);
	}
	else 
		arrival(dt);

	if (getPosition().x > _screenSize.x)
		setPosition(0, getPosition().y);
	else if (getPosition().y > _screenSize.y)
		setPosition(getPosition().x, 0);

	if (getPosition().x < 0)
		setPosition(_screenSize.x, getPosition().y);
	else if (getPosition().y < 0)
		setPosition(getPosition().x, _screenSize.y);
}

void Alien::flee(float dt)
{
	_velocity = getPosition() - _targetPosition;
	normalize(_velocity);

	move(_velocity * _speed * dt);
	_orientation = getNewOrientation(_velocity);
	setRotation(_orientation);
}
void Alien::seek(float dt)
{
	_velocity = _targetPosition - getPosition();
	normalize(_velocity);

	move(_velocity * _speed * dt);
	_orientation = getNewOrientation(_velocity);
	setRotation(_orientation);
}

void Alien::arrival(float dt)
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

float Alien::getNewOrientation(const sf::Vector2f &source)
{
	return atan2(source.y, source.x) * 180 / PI;
}

float Alien::lenght(const sf::Vector2f &a)
{
	float lenght = sqrt((a.x * a.x) + (a.y * a.y));
	return lenght;
}

float Alien::distance(sf::Vector2f a, sf::Vector2f b)
{
	sf::Vector2f difference = a - b;
	float distance = sqrt((difference.x * difference.x) + (difference.y * difference.y));
	
	return distance;
}

void Alien::normalize(sf::Vector2f &source)
{
	float length = sqrt((source.x * source.x) + (source.y * source.y));

	if (length != 0 && length != 1)
		source = sf::Vector2f(source.x / length, source.y / length);
}

void Alien::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// Apply transform of current node
	states.transform *= getTransform();
	target.draw(_sprite, states);
}