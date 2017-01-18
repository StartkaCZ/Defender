#include "Astronaut.h"
#include "ConstHolder.h"

Astronaut::Astronaut() :
	_state(State::fall),
	_currentFrame(1),
	_animationtimer(0),
	_isTarget(false),
	_isAlive(true),
	_isRunning(false),
	_lifes(1)
{
	_direction = rand() % 2;
	if (!_direction)
		_direction = -1;

	_speed = 50 + rand() % 10;
	_animationRate = 15.0f / _speed;
	_state = State::fall;

}
Astronaut::~Astronaut()
{

}
void Astronaut::Initialize(sf::Vector2f position, sf::Texture &texture, sf::FloatRect screenSize)
{
	GameObject::initialize(position, texture, ObjectType::Astronaut);
	sf::Vector2f scale = sf::Vector2f(0.2f, 0.2f);

	_screenSize = sf::Vector2u(screenSize.width, screenSize.height);

	setScale(sf::Vector2f(scale.x * _direction, scale.y));
	setSize(sf::Vector2f(scale.x * 32, scale.y * 64));
	_sprite.setOrigin(32, 64);
	_sprite.setTextureRect(sf::IntRect(0, 0, FRAME_PIXEL_WIDTH, FRAME_PIXEL_HEIGHT));
}

void Astronaut::update(float deltatime)
{
	switch (_state)
	{
	case(State::walk):
	{
		//action
		sf::Vector2f position = getPosition();
		position.x += _speed * deltatime * _direction;
		setPosition(position);
		//aniamtion
		_animationtimer += deltatime;
		if (_animationtimer > _animationRate) {
			_animationtimer = 0;
			_currentFrame++;
			if (_currentFrame > MAX_FRAME_WIDTH)
				_currentFrame = 1;

			_sprite.setTextureRect(sf::IntRect(_currentFrame * FRAME_PIXEL_WIDTH, 0, FRAME_PIXEL_WIDTH, FRAME_PIXEL_HEIGHT));
		}
		break;
	}
	case(State::capture):
	{
		_sprite.setTextureRect(sf::IntRect(0, 0, FRAME_PIXEL_WIDTH, FRAME_PIXEL_HEIGHT));
		break;
	}
	default: // case(state::fall):
	{
		_sprite.setTextureRect(sf::IntRect(256, 0, 77, 128));
		sf::Vector2f position = getPosition();
		position.y += GRAVITY * deltatime;
		setPosition(position);
		
		if (position.y > _screenSize.y * PLAYER_OFFSET_FROM_GROUND - _size.y)
		{
			_state = State::walk;
		}

		break;
	}
	}
}

void Astronaut::TakenDamage()
{
	_lifes--;

	if (_lifes == 0)
	{
		Die();
	}
}

bool Astronaut::getIsRunning()
{
	return _isRunning;
}
void  Astronaut::setIsRunning(bool isRunning)
{
	_isRunning = isRunning;
}
float Astronaut::getSpeed()
{
	return _speed;
}
void Astronaut::setSpeed(float speed)
{
	_speed = speed;
	_animationRate = 15.0f / _speed;
}

int Astronaut::getDirection()
{
	return _direction;
}
void Astronaut::setDirection(int direction)
{
	sf::Vector2f scale = getScale();
	if (direction == 1)
	{
		if(scale.x < 0)
			setScale(sf::Vector2f(-getScale().x, getScale().y));
	}
	else
	{
		if (scale.x > 0)
			setScale(sf::Vector2f(-getScale().x, getScale().y));
	}
	_direction = direction;
}

bool Astronaut::getAlive()
{
	return _isAlive;
}

void Astronaut::Die()
{
	_isAlive = false;
}


Astronaut::State Astronaut::getState() {
	return _state;
}
void Astronaut::setState(Astronaut::State state) {
	_state = state;
}



bool Astronaut::getIsTarget() {
	return _isTarget;
}
void Astronaut::setIsTarget(bool target) {
	_isTarget = target;
}