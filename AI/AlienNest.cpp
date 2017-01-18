#include "AlienNest.h"
#include "Vector2Calculator.h"
#include "ConstHolder.h"

#include "ParticleSystemManager.h"
#include "AudioManager.h"

#include <iostream>

AlienNest::AlienNest(std::vector<Interceptor*>& interceptors, std::vector<Abductor*>& abductors, std::vector<Bullet*>& abductorBullets, sf::Texture &interceptorTexture, sf::Texture &abductorTexture, sf::Texture &abductorBulletTexture)
	: _interceptorTexture(interceptorTexture)
	, _abductorTexture(abductorTexture)
	, _interceptors(interceptors)
	, _abductors(abductors)
	, _abductorbullets(abductorBullets)
	,_abductorBulletTexture(abductorBulletTexture)
	, _lifes(NEST_MAX_HEALTH)
	, _canFire(true)
	, _wondering(true)
	, _canSpawnAbductor(true)
	, _fireRateTimer(0)
	, _spawnTimer(0)
	, _angle(0)
	, _keepGoingTimes(0)
	, _wonderTimer(0)
	, _rocketsAlive(0)
{
}


AlienNest::~AlienNest()
{
}

void AlienNest::Initialize(sf::Vector2f position, sf::Texture &texture, sf::FloatRect screenSize)
{
	GameObject::initialize(position, texture, ObjectType::AlienNest);

	_screenSize = sf::Vector2u(screenSize.width, screenSize.height);

	if (rand() % 2 == 0)
	{
		_angle = 180;
	}

	Move();
}
void AlienNest::Update(float dt, sf::Vector2f playerPosition, std::vector<Meteor*>& meteors)
{
	UpdateBehaviour(playerPosition);

	FireRateTimer(dt);
	SpawnTimer(dt);
	WonderTimer(dt);

	AvoidMeteors(meteors);

	move(_velocity * NEST_MAX_SPEED * dt);

	CheckBorder();
}

void AlienNest::UpdateBehaviour(sf::Vector2f playerPosition)
{
	float distanceFromPlayer = Vector2Calculator::Distance(getPosition(), playerPosition);

	if (distanceFromPlayer < NEST_DISTANCE_TO_FIRE)
	{
		Shoot(playerPosition);
	}

	_wondering = distanceFromPlayer > NEST_DISTANCE_TO_EVADE;

	if (!_wondering)
	{
		sf::Vector2f difference = playerPosition - getPosition();
		float differenceAngle = std::atan2(difference.y, difference.x) * 180 / PI;

		NormalizeAngle();

		int angleBtw = abs(differenceAngle - _angle);

		if(angleBtw < 90)
		{
			if (differenceAngle - _angle < 0)
			{
				_angle = differenceAngle -135;
			}
			else
			{
				_angle = differenceAngle+135;
			}

			_wonderTimer = 0;
		}
	}
}

void AlienNest::Move()
{
	if (_wondering)
	{
		Orientate(15, rand() % 11);
	}
	else
	{
		Orientate(30, 10);
	}

	NormalizeAngle();

	_velocity = sf::Vector2f(cos(_angle * PI / 180), sin(_angle * PI / 180));
}

void AlienNest::Orientate(int rotateBy, int angleToAdd)
{
	float predictedYposition = getPosition().y + _velocity.y * _size.y * 3;
	if (predictedYposition < HUD_HEIGHT + _size.y)
	{
		//setPosition(getPosition().x, _size.y);
		if (_angle >= 270)
		{
			_angle += 30;
			_goClockWise = true;
		}
		else
		{
			_angle -= 30;
			_goClockWise = false;
		}
	}
	else if (predictedYposition > _screenSize.y * PLAYER_OFFSET_FROM_GROUND - _size.y)
	{
		//setPosition(getPosition().x, _screenSize.y * PLAYER_OFFSET_FROM_GROUND - _size.y);

		if (_angle >= 90)
		{
			_angle += 30;
			_goClockWise = true;
		}
		else
		{
			_angle -= 30;
			_goClockWise = false;
		}
	}
	else
	{
		if (_keepGoingTimes == 0)
		{
			_goClockWise = rand() % 2 == 0;
			_keepGoingTimes = rand() % 5 + 5;
		}
		else
		{
			_keepGoingTimes--;
		}

		int angleToAdd = 10;

		if (!_goClockWise)
		{
			angleToAdd = -angleToAdd;
		}

		_angle += angleToAdd;
	}
}

void AlienNest::NormalizeAngle()
{
	if (_angle > 360)
	{
		_angle -= 360;
	}
	else if (_angle < 0)
	{
		_angle += 360;
	}
}

void AlienNest::AvoidMeteors(std::vector<Meteor*>& meteors)
{
	for (int i = 0; i < meteors.size(); i++)
	{
		if (meteors[i]->getRegion() == _region || meteors[i]->getRegion() + 1 == _region || meteors[i]->getRegion() - 1 == _region)
		{
			float distance = Vector2Calculator::Distance(meteors[i]->getPosition(), getPosition());

			sf::Vector2f difference = meteors[i]->getPosition() - getPosition();
			float differenceAngle = std::atan2(difference.y, difference.x) * 180 / PI;

			if (differenceAngle < 0)
			{
				differenceAngle += 360;
			}

			int angleBtw = abs(differenceAngle - _angle);

			if (distance < (_size.y + _size.y * 0.5f))
			{
				if (angleBtw < 60)
				{
					_angle += 180;
				}

				NormalizeAngle();

				_velocity = sf::Vector2f(cos(_angle * PI / 180), sin(_angle * PI / 180));
			}
			else if (distance < _size.y + _size.y + _size.y + _size.y + _size.y)
			{
				if (angleBtw < 60)
				{
					if (getPosition().y + _size.y > meteors[i]->getPosition().y)
					{//i am above meteor
						if (differenceAngle < _angle)
						{
							_angle += 15;
						}
						else
						{
							_angle -= 15;
						}
					}
					else
					{//i am below meteor
						if (differenceAngle - _size.y < _angle)
						{
							_angle -= 15;
						}
						else
						{
							_angle += 15;
						}
					}

					NormalizeAngle();

					_velocity = sf::Vector2f(cos(_angle * PI / 180), sin(_angle * PI / 180));
				}
			}
		}
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
void AlienNest::WonderTimer(float dt)
{
	if (_wonderTimer > 0)
	{
		_wonderTimer -= dt;
	}
	else
	{
		Move();
		_wonderTimer = 0.50f;
	}
}

void AlienNest::Shoot(sf::Vector2f playerPosition)
{
	if (_canFire && _rocketsAlive < 2)
	{
		Interceptor* intercepor = new Interceptor(_rocketsAlive);

		sf::Vector2f direction = playerPosition - getPosition();
		Vector2Calculator::Normalize(direction);

		sf::Vector2f position = getPosition() + direction * Vector2Calculator::Lenght(_size) * 0.5f;
		intercepor->initialize(position, _interceptorTexture, playerPosition, _screenSize);
		intercepor->SetRegion(_region);

		_interceptors.push_back(intercepor);
		_canFire = false;

		AudioManager::Instance()->PlaySound(AudioManager::SoundType::ShotFired);
	}
}
void AlienNest::SpawnAbductor()
{
	if (_abductors.size() < NEST_MAX_ABDUCTORS_SPAWN_COUNT)
	{
		Abductor* abductor = new Abductor(_abductorbullets, _abductorBulletTexture);

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
	}
	else if (getPosition().x > _screenSize.x)
	{
		setPosition(0, getPosition().y);
	}

	if (getPosition().y < _size.y + HUD_HEIGHT)
	{
		setPosition(getPosition().x, _size.y + HUD_HEIGHT);
	}
	else if (getPosition().y > _screenSize.y * PLAYER_OFFSET_FROM_GROUND - _size.y)
	{
		setPosition(getPosition().x, _screenSize.y * PLAYER_OFFSET_FROM_GROUND - _size.y);
	}
}

void AlienNest::CollisionEnter(GameObject*& objectCollided)
{
	if (objectCollided->getType() == ObjectType::Projetile_PlayerLazer)
	{
		TakenDamage();
		AudioManager::Instance()->PlaySound(AudioManager::SoundType::UnitHit);
		ParticleSystemManager::Instance()->CreateParticleSystem((objectCollided->getPosition() + getPosition()) *0.5f, ParticleType::PlayerLazer);
	}
	else if (objectCollided->getType() == ObjectType::Obstacle_Meteor)
	{
		Die();
		AudioManager::Instance()->PlaySound(AudioManager::SoundType::UnitHit);
		ParticleSystemManager::Instance()->CreateParticleSystem(getPosition(), ParticleType::Death);
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
