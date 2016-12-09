#include "Player.h"

#include "ConstHolder.h"

void Player::initialize(sf::Vector2f position, sf::Texture &texture, sf::Keyboard::Key left, sf::Keyboard::Key right, sf::Keyboard::Key down, sf::Keyboard::Key up, sf::Keyboard::Key shoot, sf::Vector2u screenSize)
{
	GameObject::initialize(position, texture);

	_size = sf::Vector2f(_sprite.getTextureRect().width, _sprite.getTextureRect().height);

	_left = left;
	_right = right;
	_down = down;
	_up = up;
	_shoot = shoot;

	_screenSize = screenSize;
	_velocity = sf::Vector2f(0, 0);
}

void Player::update(float dt)
{
	readInput();

	CheckBorder();

	move(_velocity * dt);
}

void Player::CheckBorder()
{
	if (getPosition().x < 0)
		setPosition(_screenSize.x, getPosition().y);
	else if (getPosition().x > _screenSize.x)
		setPosition(0, getPosition().y);
}

void Player::readInput()
{
	if (sf::Keyboard::isKeyPressed(_left))
		MoveLeft();
	else if (sf::Keyboard::isKeyPressed(_right))
		MoveRight();
	else
		Decelerate();

	if (sf::Keyboard::isKeyPressed(_down))
		MoveDown();
	else if (sf::Keyboard::isKeyPressed(_up))
		MoveUp();
	else
		StopVerticalMovement();

	if (sf::Keyboard::isKeyPressed(_shoot))
		Shoot();
}
#pragma region Inputs

void Player::MoveLeft()
{
	if (_velocity.x > 0)
	{
		_velocity.x = 0;
	}

	if (_velocity.x > -PLAYER_MAX_SPEED)
	{
		_velocity.x -= PLAYER_ACCELERATION;
	}
	else
	{
		_velocity.x = -PLAYER_MAX_SPEED;
	}
}
void Player::MoveRight()
{
	if (_velocity.x < 0)
	{
		_velocity.x = 0;
	}

	if (_velocity.x < PLAYER_MAX_SPEED)
	{
		_velocity.x += PLAYER_ACCELERATION;
	}
	else
	{
		_velocity.x = PLAYER_MAX_SPEED;
	}
}
void Player::Decelerate()
{
	if (_velocity.x > 0)
	{
		_velocity.x -= PLAYER_DECCELERATION;

		if (_velocity.x < 0)
		{
			_velocity.x = 0;
		}
	}
	else if (_velocity.x < 0)
	{
		_velocity.x += PLAYER_DECCELERATION;

		if (_velocity.x > 0)
		{
			_velocity.x = 0;
		}
	}
}

void Player::MoveDown()
{
	if (getPosition().y + _size.y < _screenSize.y)
	{
		_velocity.y = +PLAYER_VERTICAL_SPEED;
	}
	else
	{
		StopVerticalMovement();
	}
}
void Player::MoveUp()
{
	if (getPosition().y - _size.y > 0)
	{
		_velocity.y = -PLAYER_VERTICAL_SPEED;
	}
	else
	{
		StopVerticalMovement();
	}
}
void Player::StopVerticalMovement()
{
	_velocity.y = 0;
}

void Player::Shoot()
{

}

#pragma endregion


void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// Apply transform of current node
	states.transform *= getTransform();
	target.draw(_sprite, states);
}


sf::Vector2f Player::position()
{
	return getPosition();
}