#include "AlienNest.h"
#include "Vector2Calculator.h"
#include "ConstHolder.h"


AlienNest::AlienNest(std::vector<Interceptor*>& interceptors, std::vector<Abductor*>& abductors, std::vector<Bullet*>& abductorBullets, sf::Texture &interceptorTexture, sf::Texture &abductorTexture, sf::Texture &abductorBulletTexture)
	: _interceptorTexture(interceptorTexture)
	, _abductorTexture(abductorTexture)
	, _interceptors(interceptors)
	, _abductors(abductors)
	, _abductorbullets(abductorBullets)
	,_abductorBulletTexture(abductorBulletTexture)
	, _lifes(NEST_MAX_HEALTH)
	, _isAlive(false)
	, _canFire(true)
	, _wondering(true)
	, _canSpawnAbductor(true)
	, _fireRateTimer(0)
	, _spawnTimer(0)
{
}


AlienNest::~AlienNest()
{
}

void AlienNest::Initialize(sf::Vector2f position, sf::Texture &texture, sf::FloatRect screenSize)
{
	GameObject::initialize(position, texture, ObjectType::AlienNest);

	_targetPosition = position;
	_screenSize = sf::Vector2u(screenSize.width, screenSize.height);

	_isAlive = true;
}
void AlienNest::Update(float dt, sf::Vector2f playerPosition)
{
	UpdateStatus(playerPosition);

	FireRateTimer(dt);
	SpawnTimer(dt);

	Move(dt);

	CheckBorder();
}

void AlienNest::UpdateStatus(sf::Vector2f playerPosition)
{
	float distanceFromPlayer = Vector2Calculator::Distance(getPosition(), playerPosition);

	if (distanceFromPlayer < NEST_DISTANCE_TO_FIRE)
	{
		Shoot(playerPosition);
		_wondering = false;
	}
	else if (distanceFromPlayer < NEST_DISTANCE_TO_EVADE)
	{
		_wondering = false;
	}
	else
	{
		_wondering = true;
	}

	_targetPosition = playerPosition;
}

void AlienNest::Move(float dt)
{
	if (_wondering)
	{
		Wonder(dt);
	}
	else
	{
		Evade(dt);
	}
}

void AlienNest::Wonder(float dt)
{
	_velocity = _targetPosition - getPosition();
	Vector2Calculator::Normalize(_velocity);

	move(_velocity * NEST_MAX_SPEED * dt);
}
void AlienNest::Evade(float dt)
{
	_velocity = getPosition() - _targetPosition;
	Vector2Calculator::Normalize(_velocity);

	move(_velocity * NEST_MAX_SPEED * dt);
}

void AlienNest::FireRateTimer(float dt)
{
	if (!_canFire)
	{
		if (_fireRateTimer > NEST_FIRE_RATE)
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
void AlienNest::SpawnTimer(float dt)
{
	if (_spawnTimer > NEST_SPAWN_RATE)
	{
		SpawnAbductor();
		_spawnTimer = 0;
	}
	else
	{
		_spawnTimer += dt;
	}
}

void AlienNest::Shoot(sf::Vector2f playerPosition)
{
	if (_canFire)
	{
		Interceptor* intercepor = new Interceptor(_rocketsAlive);

		sf::Vector2f direction = playerPosition - getPosition();
		Vector2Calculator::Normalize(direction);

		sf::Vector2f position = getPosition() + direction * Vector2Calculator::Lenght(_size) * 0.5f;
		intercepor->initialize(position, _interceptorTexture, playerPosition, _screenSize);

		_interceptors.push_back(intercepor);
		_canFire = false;
	}
}
void AlienNest::SpawnAbductor()
{
	if (_abductors.size() < NEST_MAX_ABDUCTORS_SPAWN_COUNT)
	{
		Abductor* abductor = new Abductor(_abductorbullets, _abductorBulletTexture);

		abductor->initialize(getPosition(), _abductorTexture, sf::FloatRect(0, 0, _screenSize.x, _screenSize.y));

		_abductors.push_back(abductor);
	}
}

void AlienNest::CheckBorder()
{
	if (getPosition().x < 0)
	{
		setPosition(_screenSize.x, getPosition().y);
		//Wonder Again

	}
	else if (getPosition().x > _screenSize.x)
	{
		setPosition(0, getPosition().y);
		//Wonder Again

	}

	if (getPosition().y < _size.y)
	{
		setPosition(getPosition().x, _size.y);
		//Wonder Again

	}
	else if (getPosition().y > _screenSize.y * PLAYER_OFFSET_FROM_GROUND - _size.y)
	{
		setPosition(getPosition().x, _screenSize.y * PLAYER_OFFSET_FROM_GROUND - _size.y);
		//Wonder Again

	}
}

void AlienNest::TakenDamage()
{
	_lifes--;

	if (_lifes == 0)
	{
		Die();
	}
}
void AlienNest::Die()
{
	_isAlive = false;
}

bool AlienNest::getAlive() const
{
	return _isAlive;
}
