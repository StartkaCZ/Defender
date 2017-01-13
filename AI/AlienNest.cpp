#include "AlienNest.h"
#include "Vector2Calculator.h"
#include "ConstHolder.h"

AlienNest::AlienNest(std::vector<Interceptor*>& interceptors, std::vector<Abductor*>& abductors, sf::Texture &interceptorTexture, sf::Texture &abductorTexture)
	: _interceptorTexture(interceptorTexture)
	, _abductorTexture(abductorTexture)
	, _interceptors(interceptors)
	, _abductors(abductors)
	, _lifes(NEST_MAX_HEALTH)
	, _isAlive(false)
	, _canFire(true)
	, _wondering(true)
	, _canSpawnAbductor(true)
	, _movingLeft(rand() % 2 == 0)
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
	//UpdateStatus(playerPosition);

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
	CalculateTargetPoint();

	move(_velocity * NEST_MAX_SPEED * dt);
}

void AlienNest::Evade(float dt)
{
	_velocity = getPosition() - _targetPosition;
	Vector2Calculator::Normalize(_velocity);

	move(_velocity * NEST_MAX_SPEED * dt);
}

void AlienNest::CalculateTargetPoint()
{
	if (Vector2Calculator::Distance(_targetPosition, getPosition()) < _size.x)
	{
		if (_movingLeft)
		{
			_targetPosition.x = rand() % (int)(_screenSize.x - getPosition().x - _size.x - _size.x) + 1 + getPosition().x + _size.x;

			float differnce = _targetPosition.x - getPosition().x;
			float limit = _screenSize.y * 0.1f;

			if (differnce > limit)
			{
				_targetPosition.x = _targetPosition.x - (differnce - limit);
			}
		}
		else
		{
			_targetPosition.x = rand() % (int)(getPosition().x - _size.x) + 1 + _size.x;

			sf::Vector2f differnce = sf::Vector2f(getPosition().x - _targetPosition.x, getPosition().y - _targetPosition.y);
			sf::Vector2f limit = sf::Vector2f(_screenSize.x * 0.01f, _screenSize.y * 0.1f);

			if (differnce.x > limit.x)
			{
				_targetPosition.x = _targetPosition.x + (differnce.x - limit.x);
			}
			if (differnce.y > limit.y)
			{
				_targetPosition.x = _targetPosition.x + (differnce.y - limit.y);
			}
		}

		_targetPosition.y = rand() % (int)(_screenSize.y * PLAYER_OFFSET_FROM_GROUND - _size.y - _size.y) + _size.y;

		_velocity = _targetPosition - getPosition();
		Vector2Calculator::Normalize(_velocity);
	}
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
		intercepor->SetRegion(_region);

		_interceptors.push_back(intercepor);
		_canFire = false;
	}
}
void AlienNest::SpawnAbductor()
{
	if (_abductors.size() < NEST_MAX_ABDUCTORS_SPAWN_COUNT)
	{
		Abductor* abductor = new Abductor();

		abductor->initialize(getPosition(), _abductorTexture, sf::FloatRect(0, 0, _screenSize.x, _screenSize.y));
		abductor->SetRegion(_region);

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
