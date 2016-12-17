#include "Player.h"

#include "ConstHolder.h"


Player::Player()
	: _fireRateTimer(0)
	, _nukeTimer(0)
	, _superJumpTimer(0)
	, _velocity(sf::Vector2f(0, 0))
	, _nukeCount(1)
	, _superJumpCount(1)
	, _canFire(true)
	, _canNuke(true)
	, _canSuperJump(true)
{

}

void Player::initialize(sf::Vector2f position, sf::Texture &texture, sf::FloatRect screenSize)
{
	GameObject::initialize(position, texture);

	_size = sf::Vector2f(_sprite.getTextureRect().width, _sprite.getTextureRect().height);

	_screenSize = sf::Vector2u(screenSize.width, screenSize.height);
}


void Player::update(float dt)
{
	readInput();
	CheckBorder();

	FireRateTimer(dt);
	NukeTimer(dt);
	SuperJumpTimer(dt);

	move(_velocity * dt);
}

#pragma region Timers

void Player::FireRateTimer(float dt)
{
	if (!_canFire)
	{
		if (_fireRateTimer > PLAYER_FIRE_RATE)
		{
			_canFire = true;
			_fireRateTimer = 0;
		}
		else
		{
			_fireRateTimer += dt;
		}
	}
}
void Player::NukeTimer(float dt)
{
	if (!_canNuke)
	{
		if (_nukeTimer > PLAYER_NUKE_TIMER)
		{
			_canNuke = true;
			_nukeTimer = 0;
		}
		else
		{
			_nukeTimer += dt;
		}
	}
}
void Player::SuperJumpTimer(float dt)
{
	if (!_canSuperJump)
	{
		if (_superJumpTimer > PLAYER_SUPER_JUMP_TIMER)
		{
			_canSuperJump = true;
			_superJumpTimer = 0;
		}
		else
		{
			_superJumpTimer += dt;
		}
	}
}

#pragma endregion

//FOR TESTING
void Player::CheckBorder()
{
	if (getPosition().x < 0)
		setPosition(_screenSize.x, getPosition().y);
	else if (getPosition().x > _screenSize.x)
		setPosition(0, getPosition().y);
}

void Player::readInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		MoveLeft();
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		MoveRight();
	else
		Decelerate();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		MoveDown();
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
		MoveUp();
	else
		StopVerticalMovement();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
		Shoot();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1))
		Nuke();
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2))
		SuperJump();
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
	if (getPosition().y + _size.y < _screenSize.y * PLAYER_OFFSET_FROM_GROUND)
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

//Shoots lazers
void Player::Shoot()
{
	if (_canFire)
	{

		_canFire = false;
	}
}
//Kills all enemies
void Player::Nuke()
{
	if (_canNuke && _nukeCount > 0)
	{

		_nukeCount--;
		_canNuke = false;
	}
}
//Random Teleportation			
void Player::SuperJump()
{
	if (_canSuperJump && _superJumpCount > 0)
	{
		float x = (rand() % _screenSize.x - _size.x - _size.x) + _size.x;
		float y = (rand() % _screenSize.y * PLAYER_OFFSET_FROM_GROUND - _size.y - _size.y) + _size.y + _size.y;

		setPosition(x, y);

		_superJumpCount--;
		_canSuperJump = false;
	}
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