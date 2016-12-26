#include "Player.h"

#include "ConstHolder.h"


Player::Player(std::vector<Projectile*>& projectiles, sf::Texture &lazerTexture)
	: _lazerTexture(lazerTexture)
	, _fireRateTimer(0)
	, _nukeTimer(0)
	, _superJumpTimer(0)
	, _velocity(sf::Vector2f(0, 0))
	, _nukeCount(1)
	, _superJumpCount(1)
	, _canFire(true)
	, _canNuke(true)
	, _canSuperJump(true)
	, _movingLeft(false)
	, _hasNuked(false)
	, _projectiles(projectiles)
	, _lifes(PLAYER_MAX_LIVES)
{

}

void Player::Initialize(sf::Vector2f position, sf::Texture &texture, sf::FloatRect screenSize)
{
	GameObject::initialize(position, texture, ObjectType::Player);

	_screenSize = sf::Vector2u(screenSize.width, screenSize.height);
}


void Player::Update(float dt)
{
	ReadInput();
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
	{
		setPosition(_screenSize.x, getPosition().y);
	}
	else if (getPosition().x > _screenSize.x)
	{
		setPosition(0, getPosition().y);
	}
}

void Player::ReadInput()
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
	if (!_movingLeft)
	{
		_velocity.x = 0;
		_movingLeft = true;
		setScale(-getScale().x, getScale().y);
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
	if (_movingLeft)
	{
		_velocity.x = 0;
		_movingLeft = false;
		setScale(-getScale().x, getScale().y);
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
	if (getPosition().y + _size.y * 2.5f < _screenSize.y * PLAYER_OFFSET_FROM_GROUND)
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
		Projectile* lazer = new Projectile();
		
		if (_movingLeft)
		{
			sf::Vector2f position = sf::Vector2f(getPosition().x - _size.x, getPosition().y);
			lazer->initialize(position, _lazerTexture, sf::Vector2f(-1, 0), _screenSize, ObjectType::Projetile_PlayerLazer);
		}
		else
		{
			sf::Vector2f position = sf::Vector2f(getPosition().x + _size.x, getPosition().y);
			lazer->initialize(position, _lazerTexture, sf::Vector2f(1, 0), _screenSize, ObjectType::Projetile_PlayerLazer);
		}

		_projectiles.push_back(lazer);
		_canFire = false;
	}
}
//Kills all enemies
void Player::Nuke()
{
	if (_canNuke && _nukeCount > 0)
	{
		_hasNuked = true;
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


void Player::NukingOver()
{
	_hasNuked = true;
}

void Player::CollectedPowerUp(ObjectType powerUp)
{
	switch (powerUp)
	{
	case ObjectType::PowerUp_SuperJump:
		_superJumpCount++;
		break;

	default:
		break;
	}

}
void Player::TakenDamage()
{
	_lifes--;
}


bool Player::hasNuked()
{
	return _hasNuked;
}