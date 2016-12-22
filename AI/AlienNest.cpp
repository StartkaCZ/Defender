#include "AlienNest.h"
#include "Vector2Calculator.h"
#include "ConstHolder.h"


AlienNest::AlienNest(std::vector<Projectile*>& projectiles, std::vector<Abductor*>& abductors)
	: _projectiles(projectiles)
	, _abductors(_abductors)
	, _lifes(2)
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

void AlienNest::Initialize(sf::Vector2f position, sf::Texture &texture, sf::Texture &lazerTexture, sf::Texture &abductorTexture, sf::FloatRect screenSize)
{
	GameObject::initialize(position, texture, ObjectType::Player);

	_lazerTexture = lazerTexture;
	_abductorTexture = abductorTexture;

	_screenSize = sf::Vector2u(screenSize.width, screenSize.height);
}
void AlienNest::Update(float dt, sf::Vector2f playerPosition)
{
	UpdateStatus(playerPosition);

	FireRateTimer(dt);
	SpawnTimer(dt);

	Move(dt);
}

void AlienNest::UpdateStatus(sf::Vector2f playerPosition)
{
	float distanceFromPlayer = Vector2Calculator::Distance(getPosition(), playerPosition);

	if (distanceFromPlayer < NEST_DISTANCE_TO_FIRE)
	{
		Shoot();
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
		Wonder();
	}
	else
	{
		Evade();
	}
}

void AlienNest::Wonder()
{

}
void AlienNest::Evade()
{

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
	if (!_canSpawnAbductor)
	{
		if (_spawnTimer > NEST_SPAWN_RATE)
		{
			_canSpawnAbductor = true;
			_spawnTimer = 0;
		}
		else
		{
			_spawnTimer += dt;
		}
	}
}

void AlienNest::Shoot()
{
	if (_canFire)
	{
		Projectile* intercepor = new Projectile();

		sf::Vector2f position = sf::Vector2f(getPosition().x + _size.x, getPosition().y);
		intercepor->initialize(position, _lazerTexture, sf::Vector2f(1, 0), _screenSize, ObjectType::Projetile_PlayerLazer);

		_projectiles.push_back(intercepor);
		_canFire = false;
	}
}
void AlienNest::SpawnAbductor()
{
	
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
