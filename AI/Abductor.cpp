#include "Abductor.h"
#include "ConstHolder.h"
#include <math.h>

#define PI 3.141592635

Abductor::Abductor(std::vector<Bullet*>& bullets, sf::Texture &bulletTexture)
	: _target(nullptr), _state(State::flock), _bullets(bullets), _bulletTexture(bulletTexture), _lifes(1), _isAlive(true), _canFire(true)
{
}

Abductor::~Abductor()
{
	delete _target;
}

void Abductor::initialize(sf::Vector2f position, sf::Texture &texture, sf::FloatRect screenSize)
{
	GameObject::initialize(position, texture, ObjectType::Abductor);

	_screenSize = sf::Vector2u(screenSize.width, screenSize.height);
	acceleration = Pvector(0, 0);
	velocity = Pvector(rand() % 6 - 2,0); // Allows for range of -2 -> 2
	maxSpeed = 5;
	maxForce = 0.5f;
	location =  Pvector(position.x, position.y);
}




// Adds force Pvector to current force Pvector
void Abductor::applyForce(Pvector force)
{
	acceleration.addVector(force);
}

// Function that checks and modifies the distance
// of a boid if it breaks the law of separation.
Pvector Abductor::Separation(vector<Abductor*> boids, sf::Vector2f playerPos)
{
	// If the boid we're looking at is a predator, do not run the separation
	// algorithm

	// Distance of field of vision for separation between boids
	float desiredseparation = 50;

	Pvector steer(0, 0);
	int count = 0;
	// For every boid in the system, check if it's too close
	for (int i = 0; i < boids.size(); i++) 
	{
		if (boids[i]->getState() == State::flock)
		{
			// Calculate distance from current boid to boid we're looking at
			float d = location.distance(boids[i]->location);
			// If this is a fellow boid and it's too close, move away from it
			if ((d > 0) && (d < desiredseparation))
			{
				Pvector diff(0, 0);
				diff = diff.subTwoVector(location, boids[i]->location);
				diff.normalize();
				diff.divScalar(d);      // Weight by distance
				steer.addVector(diff);
				count++;
			}
		}
	}
	
	Pvector playerPosition = Pvector(playerPos.x, playerPos.y);
	float d = location.distance(playerPosition);
	if ((d > 0) && (d < desiredseparation + 120))
	{
		Pvector pred(0, 0);
		pred = pred.subTwoVector(location, playerPosition);
		pred.mulScalar(1000);
		steer.addVector(pred);
		count++;
	}
	// Adds average difference of location to acceleration
	if (count > 0)
		steer.divScalar((float)count);
	if (steer.magnitude() > 0)
	{
		// Steering = Desired - Velocity
		steer.normalize();
		steer.mulScalar(maxSpeed);
		steer.subVector(velocity);
		steer.limit(maxForce);
	}
	return steer;
}

// Alignment calculates the average velocity in the field of view and 
// manipulates the velocity of the Boid passed as parameter to adjust to that
// of nearby boids.
Pvector Abductor::Alignment(vector<Abductor*> Boids)
{
	float neighbordist = 90;

	Pvector sum(0, 0);
	int count = 0;
	for (int i = 0; i < Boids.size(); i++)
	{
		if (Boids[i]->getState() == State::flock)
		{
			float d = location.distance(Boids[i]->location);
			if ((d > 0) && (d < neighbordist)) // 0 < d < 50
			{
				sum.addVector(Boids[i]->velocity);
				count++;
			}
		}
	}
	// If there are boids close enough for alignment...
	if (count > 0)
	{
		sum.divScalar((float)count);// Divide sum by the number of close boids (average of velocity)
		sum.normalize();	   		// Turn sum into a unit vector, and
		sum.mulScalar(maxSpeed);    // Multiply by maxSpeed
									// Steer = Desired - Velocity
		Pvector steer;
		steer = steer.subTwoVector(sum, velocity); //sum = desired(average)  
		steer.limit(maxForce);
		return steer;
	}
	else {
		Pvector temp(0, 0);
		return temp;
	}
}

// Cohesion finds the average location of nearby boids and manipulates the 
// steering force to move in that direction.
Pvector Abductor::Cohesion(vector<Abductor*> Boids)
{
	float neighbordist = 90;

	Pvector sum(0, 0);
	int count = 0;
	for (int i = 0; i < Boids.size(); i++)
	{
		if (Boids[i]->getState() == State::flock)
		{
			float d = location.distance(Boids[i]->location);
			if ((d > 0) && (d < neighbordist))
			{
				sum.addVector(Boids[i]->location);
				count++;
			}
		}
	}
	if (count > 0)
	{
		sum.divScalar(count);
		return seek(sum);
	}
	else {
		Pvector temp(0, 0);
		return temp;
	}
}

// Seek function limits the maxSpeed, finds necessary steering force and
// normalizes the vectors.
Pvector Abductor::seek(Pvector v)
{
	Pvector desired;
	desired.subVector(v);  // A vector pointing from the location to the target
						   // Normalize desired and scale to maximum speed
	desired.normalize();
	desired.mulScalar(maxSpeed);
	acceleration.subTwoVector(desired, velocity);
	acceleration.limit(maxForce);  // Limit to maximum steering force
	return acceleration;
}

//Update modifies velocity, location, and resets acceleration with values that
//are given by the three laws.
void Abductor::update(float dt, sf::Vector2f playerPos)
{
	FireRateTimer(dt);
	//Shoot(playerPos);
	borders();

	//To make the slow down not as abrupt
	acceleration.mulScalar(.25f);
	// Update velocity
	velocity.addVector(acceleration  * dt);
	// Limit speed
	velocity.limit(maxSpeed);
	location.addVector(velocity);
	// Reset accelertion to 0 each cycle
	acceleration.mulScalar(0);

	setPosition(sf::Vector2f(location.x, location.y));
}

void Abductor::FireRateTimer(float dt)
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

void Abductor::Shoot(sf::Vector2f playerPosition)
{
	if (_canFire)
	{
		Bullet* bullet = new Bullet();

		sf::Vector2f direction = playerPosition - getPosition();
		Vector2Calculator::Normalize(direction);

		//sf::Vector2f position = getPosition() + direction * Vector2Calculator::Lenght(_size) * 0.5f;
		bullet->initialize(getPosition(), _bulletTexture, playerPosition, _screenSize);

		_bullets.push_back(bullet);
		_canFire = false;
	}
}

//Applies all three laws for the flock of boids and modifies to keep them from
//breaking the laws.
void Abductor::flock(vector<Abductor*> v,  sf::Vector2f playerPos)
{
	

	Pvector sep = Separation(v, playerPos);
	Pvector ali = Alignment(v);
	Pvector coh = Cohesion(v);

	if (location.y > GROUND_LEVEL)
	{
		Pvector force(0,0);
		force.y = location.y - GROUND_LEVEL;

		sep.addVector(Pvector(0, -force.y * 0.18f));
	}
	else if (location.y < 0)
	{
		Pvector force(0, 0);
		force.y = location.y - 0;

		sep.addVector(Pvector(0, -force.y * 0.18f));
	}

	// Arbitrarily weight these forces
	sep.mulScalar(52.5);
	ali.mulScalar(35.0 ); // Might need to alter weights for different characteristics
	coh.mulScalar(35.0);
	// Add the force vectors to acceleration
	applyForce(sep);
	applyForce(ali);
	applyForce(coh);
	
	
}
void Abductor::findAstronaut(Astronaut* astro)
{
	//check distance of abductor and astro
	Pvector targetPos = Pvector(astro->getPosition().x, astro->getPosition().y);
	Pvector currentPos = Pvector(getPosition().x, getPosition().y);
	Pvector ab = targetPos - currentPos;
	if (ab.magnitude() < 200) 
	{
		
		if (_target == nullptr)
		{
			if (!astro->getIsTarget())
			{
				astro->setIsTarget(true);
				_state = State::seek;
				_target = astro;
			}
		}
	
	}
}

void Abductor::seek()
{
	Pvector targetPos = Pvector(_target->getPosition().x, _target->getPosition().y - 32);
	Pvector currentPos = Pvector(getPosition().x, getPosition().y);
	Pvector ab = targetPos - currentPos;
	ab.normalize();
	velocity = ab * 5.0f;
	
}

bool Abductor::flee(sf::Vector2f playerPos)
{
	Pvector steer(0,0);
	Pvector playerPosition = Pvector(playerPos.x, playerPos.y);
	float d = location.distance(playerPosition);
	if ((d > 0) && (d <170))
	{
		Pvector pred(0, 0);
		pred = pred.subTwoVector(location, playerPosition);
		pred.mulScalar(1000);
		steer.addVector(pred);
	}


	steer.normalize();
	steer.mulScalar(maxSpeed);
	steer.y =  -1.5f ;
	steer.subVector(velocity);
	steer.limit(maxForce);
	

	steer.mulScalar(65.5);
	
	applyForce(steer);

	_target->setPosition(getPosition().x + _targetPosOffset.x, getPosition().y + _targetPosOffset.y);
	if (getPosition().y + getSize().y * 2 + _target->getSize().y * 2 < 0)
	{
		return true;
	}
	return false;
}

// Checks if boids go out of the window and if so, wraps them around to the other side.
void Abductor::borders()
{
	if (location.x < 0) location.x += _screenSize.x;
	//if (location.y < -200) location.y += _screenSize.y + 200;
	if (location.x > 2400) location.x -= _screenSize.x;
	
}

void Abductor::TakenDamage()
{
	_lifes--;

	if (_lifes == 0)
	{
		Die();
	}
}

void Abductor::Die()
{
	_isAlive = false;
	if (_target != nullptr)
	{
		_target->setIsTarget(false);

		if (_target->getState() == Astronaut::State::capture)
		{
			_target->setState(Astronaut::State::fall);
		}
		_target = nullptr;
	}
}

bool Abductor::getAlive()
{
	return _isAlive;
}

Astronaut* Abductor::getTarget() {
	return _target;
}

Abductor::State Abductor::getState() {
	return _state;
}
void Abductor::setState(Abductor::State state) {
	_state = state;
}

void Abductor::setTargetPosOffset(sf::Vector2f targetPosOffset)
{
	_targetPosOffset = targetPosOffset;
}