#include "Mutant.h"
#include "ConstHolder.h"
#include <math.h>

#include "ParticleSystemManager.h"
#include "AudioManager.h"

#define PI 3.141592635

Mutant::Mutant(std::vector<Bullet*>& bullets, sf::Texture &bulletTexture)
	: _state(State::seek), 
	_bullets(bullets), 
	_bulletTexture(bulletTexture),
	_lifes(2), 
	_isAlive(true),
	_canFire(true),
	_fireRateTimer(0)
{
}

Mutant::~Mutant()
{
	
}

void Mutant::initialize(sf::Vector2f position, sf::Texture &texture, sf::FloatRect screenSize)
{
	GameObject::initialize(position, texture, ObjectType::Mutant);

	_screenSize = sf::Vector2u(screenSize.width, screenSize.height);
	_acceleration = Pvector(0, 0);
	_velocity = Pvector(rand() % 6 - 2, 0); // Allows for range of -2 -> 2
	_maxSpeed = 5;
	_maxForce = 0.5f;
	_location = Pvector(position.x, position.y);
}




// Adds force Pvector to current force Pvector
void Mutant::applyForce(Pvector force)
{
	_acceleration.addVector(force);
}


//Update modifies velocity, location, and resets acceleration with values that
//are given by the three laws.
void Mutant::update(float dt)
{
	FireRateTimer(dt);
	borders();

	//To make the slow down not as abrupt
	_acceleration.mulScalar(.25f);
	// Update velocity
	_velocity.addVector(_acceleration );
	// Limit speed
	_velocity.limit(_maxSpeed);
	_location.addVector(_velocity);
	// Reset accelertion to 0 each cycle
	_acceleration.mulScalar(0);

	setPosition(sf::Vector2f(_location.x, _location.y));
}

void Mutant::FireRateTimer(float dt)
{
	if (!_canFire)
	{
		if (_fireRateTimer > ABDUCTOR_FIRE_RATE)
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

void Mutant::Shoot(sf::Vector2f diretion)
{
	if (_canFire)
	{
		Bullet* bullet = new Bullet();
		bullet->initialize(getPosition(), _bulletTexture, diretion, _screenSize);
		bullet->SetRegion(_region);
		_bullets.push_back(bullet);
		_canFire = false;

		AudioManager::Instance()->PlaySound(AudioManager::SoundType::ShotFired);
	}
}

sf::Vector2f Mutant::getFireDirection(sf::Vector2f p)
{
	Pvector direction = direction.subTwoVector(Pvector(p.x,p.y), _location);
	direction.normalize();
	return sf::Vector2f(direction.x, direction.y);
}

void Mutant::swarm(vector <Mutant*> v, sf::Vector2f p)
{
	Pvector sum(0, 0);
	Pvector PlayerPos(p.x, p.y);
	Pvector direction = direction.subTwoVector(_location, PlayerPos);
	float distanceToPlayer = direction.magnitude();
	direction.normalize();
	Pvector TargetPos(PlayerPos.x + direction.x * 220, PlayerPos.y + direction.y * 220);
	Pvector VectorToTargetPos = VectorToTargetPos.subTwoVector(TargetPos, _location);

	if (distanceToPlayer > 600)
	{
		_state = State::seek;
		return;
	}
	else if (distanceToPlayer < 150)
	{
		direction.normalize();
		direction.mulScalar(-2.5f);
		sum.subVector(direction);
	}
	else
	{
		VectorToTargetPos.normalize();
		VectorToTargetPos.mulScalar(0.5f);
		sum.addVector(VectorToTargetPos);
	}

	float A = 0.3f;
	float N = 0.4f;

	float B = 0.45f;
	float M = 0.5f;

	for (int i = 0; i < v.size(); i++)
	{
		if (v[i]->getState() == Mutant::State::swarm)
		{
			Pvector	R;
			R = R.subTwoVector(_location, v[i]->getLocation());

			float D = R.magnitude();

			if (D > 0)
			{
				float U = -A / pow(D, N) + B / pow(D, M);
				R.normalize();

				R.mulScalar(U * 700);
				sum.addVector(R);

			}
		}
	}
	float groundLevel = _screenSize.y * PLAYER_OFFSET_FROM_GROUND;

	if (_location.y > groundLevel)
	{
		Pvector force(0, 0);
		force.y = _location.y - groundLevel;

		sum.addVector(Pvector(0, -force.y * 0.18f));
	}
	else if (_location.y < HUD_HEIGHT)
	{
		Pvector force(0, 0);
		force.y = _location.y - HUD_HEIGHT ;

		sum.addVector(Pvector(0, -force.y * 0.18f));
	}

	applyForce(sum);
}

void Mutant::seek(sf::Vector2f p)
{
	Pvector player(p.x, p.y);
	Pvector AB = AB.subTwoVector(player, _location);
	
	
	if (AB.magnitude() < 600)
	{
		_state = State::swarm;
	}
	else
	{
		AB.normalize();
		_velocity = AB * (_maxSpeed - 2.0f);
		//AB.limit(maxSpeed);
		//applyForce(AB);
	}
}

void Mutant::CollisionEnter(GameObject*& objectCollided)
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

// Checks if boids go out of the window and if so, wraps them around to the other side.
void Mutant::borders()
{
	if (_location.x < 0) _location.x += _screenSize.x;
	//if (location.y < -200) location.y += _screenSize.y + 200;
	if (_location.x > _screenSize.x) _location.x -= _screenSize.x;

}

void Mutant::TakenDamage()
{
	_lifes--;

	if (_lifes == 0)
	{
		Die();
	}
}

void Mutant::Die()
{
	_isAlive = false;
	AudioManager::Instance()->PlaySound(AudioManager::SoundType::UnitDestroyed);
	ParticleSystemManager::Instance()->CreateParticleSystem(getPosition(), ParticleType::Death);
}

bool Mutant::getAlive()
{
	return _isAlive;
}

Mutant::State Mutant::getState() {
	return _state;
}

void Mutant::setState(Mutant::State state) {
	_state = state;
}

Pvector	Mutant::getLocation()
{
	return _location;
}

void Mutant::setLocation(Pvector loc)
{
	_location = loc;
}

bool Mutant::getCanFire()
{
	return _canFire;
};
void Mutant::setCanFire(bool canFire)
{
	_canFire = canFire;
}