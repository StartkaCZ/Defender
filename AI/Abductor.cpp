#include "Abductor.h"
/*
Abductor::Abductor()
{
}


Abductor::~Abductor()
{
}*/

void Abductor::initialize(sf::Vector2f position, sf::Texture &texture, sf::FloatRect screenSize)
{
	GameObject::initialize(position, texture, ObjectType::Abductor);

	_screenSize = sf::Vector2u(screenSize.width, screenSize.height);
	acceleration = Pvector(0, 0);
	velocity = Pvector(rand() % 3 - 2, rand() % 3 - 2); // Allows for range of -2 -> 2
	maxSpeed = 3.5;
	maxForce = 0.5;
	location =  Pvector(position.x, position.y);
}

void Abductor::update(float dt, sf::Vector2f playerPosition)
{

}


#define PI 3.141592635

using namespace std;

// =============================================== //
// ======== Boid Functions from Boid.h =========== //
// =============================================== //

// Adds force Pvector to current force Pvector
void Abductor::applyForce(Pvector force)
{
	acceleration.addVector(force);
}

// Function that checks and modifies the distance
// of a boid if it breaks the law of separation.
Pvector Abductor::Separation(vector<Abductor*> &boids)
{
	// If the boid we're looking at is a predator, do not run the separation
	// algorithm

	// Distance of field of vision for separation between boids
	float desiredseparation = 20;

	Pvector steer(0, 0);
	int count = 0;
	// For every boid in the system, check if it's too close
	for (int i = 0; i < boids.size(); i++)
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
		// If current boid is a predator and the boid we're looking at is also
		// a predator, then separate only slightly 
		if ((d > 0) && (d < desiredseparation) && predator == true && boids[i]->predator == true)
		{
			Pvector pred2pred(0, 0);
			pred2pred = pred2pred.subTwoVector(location, boids[i]->location);
			pred2pred.normalize();
			pred2pred.divScalar(d);
			steer.addVector(pred2pred);
			count++;
		}
		// If current boid is not a predator, but the boid we're looking at is
		// a predator, then create a large separation Pvector
		else if ((d > 0) && (d < desiredseparation + 70) && boids[i]->predator == true)
		{
			Pvector pred(0, 0);
			pred = pred.subTwoVector(location, boids[i]->location);
			pred.mulScalar(900);
			steer.addVector(pred);
			count++;
		}
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
Pvector Abductor::Alignment(vector<Abductor*> &Boids)
{
	// If the boid we're looking at is a predator, do not run the alignment
	// algorithm
	//if (predator == true)
	//	return Pvector(0,0);
	float neighbordist = 50;

	Pvector sum(0, 0);
	int count = 0;
	for (int i = 0; i < Boids.size(); i++)
	{
		float d = location.distance(Boids[i]->location);
		if ((d > 0) && (d < neighbordist)) // 0 < d < 50
		{
			sum.addVector(Boids[i]->velocity);
			count++;
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
Pvector Abductor::Cohesion(vector<Abductor*> &Boids)
{
	// If the boid we're looking at is a predator, do not run the cohesion
	// algorithm
	//if (predator == true)
	//	return Pvector(0,0);

	float neighbordist = 50;

	Pvector sum(0, 0);
	int count = 0;
	for (int i = 0; i < Boids.size(); i++)
	{
		float d = location.distance(Boids[i]->location);
		if ((d > 0) && (d < neighbordist))
		{
			sum.addVector(Boids[i]->location);
			count++;
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
	// Steering = Desired minus Velocity
	acceleration.subTwoVector(desired, velocity);
	acceleration.limit(maxForce);  // Limit to maximum steering force
	return acceleration;
}

//Update modifies velocity, location, and resets acceleration with values that
//are given by the three laws.
void Abductor::update()
{
	//To make the slow down not as abrupt
	acceleration.mulScalar(.4);
	// Update velocity
	velocity.addVector(acceleration);
	// Limit speed
	velocity.limit(maxSpeed);
	location.addVector(velocity);
	// Reset accelertion to 0 each cycle
	acceleration.mulScalar(0);

	setPosition(sf::Vector2f(location.x, location.y));
}

//Run runs flock on the flock of boids for each boid.
//Which applies the three rules, modifies accordingly, updates data, checks is data is
//out of range, fixes that for SFML, and renders it on the window.
void Abductor::run(vector <Abductor*> &v, Astronaut* astro)
{
	
	switch (_state)
	{
	case Abductor::state::flock:
	{
		flock(v);
		
		Pvector targetPos = Pvector(astro->getPosition().x, astro->getPosition().y);
		Pvector currentPos = Pvector(getPosition().x, getPosition().y);
		Pvector ab =  targetPos - currentPos;
		if (ab.magnitude() < 1000) {
			_state = state::attack;
			_target = astro;
		}
		
		break;
	}
	case Abductor::state::attack:
	{
		Pvector targetPos = Pvector(_target->getPosition().x, _target->getPosition().y);
		Pvector currentPos = Pvector(getPosition().x, getPosition().y);
		Pvector ab = targetPos - currentPos;
		ab.normalize();
		velocity = ab * 3.5f;
		break;
	}
	case Abductor::state::flee:
		break;
	default:
		break;
	}
	
	update();
	borders();
}

//Applies all three laws for the flock of boids and modifies to keep them from
//breaking the laws.
void Abductor::flock(vector<Abductor*> &v)
{
	Pvector sep = Separation(v);
	Pvector ali = Alignment(v);
	Pvector coh = Cohesion(v);
	// Arbitrarily weight these forces
	sep.mulScalar(1.5);
	ali.mulScalar(1.0); // Might need to alter weights for different characteristics
	coh.mulScalar(1.0);
	// Add the force vectors to acceleration
	applyForce(sep);
	applyForce(ali);
	applyForce(coh);
}

// Checks if boids go out of the window and if so, wraps them around to the other side.
void Abductor::borders()
{
	if (location.x < 0) location.x += _screenSize.x;
	if (location.y < 0) location.y += _screenSize.y;
	if (location.x > 1000) location.x -= _screenSize.x;
	if (location.y > 1000) location.y -= _screenSize.y;
}

// Calculates the angle for the velocity of a boid which allows the visual 
// image to rotate in the direction that it is going in.
float Abductor::angle(Pvector v)
{
	// From the definition of the dot product
	float angle = (float)(atan2(v.x, -v.y) * 180 / PI);
	return angle;
}

void Abductor::swarm(vector <Abductor*> &v)
{
	/*		Lenard-Jones Potential function
	Vector R = me.position - you.position
	Real D = R.magnitude()
	Real U = -A / pow(D, N) + B / pow(D, M)
	R.normalise()
	force = force + R*U
	*/
	Pvector	R;
	Pvector sum(0, 0);

	// Your code here..

	applyForce(sum);
	update();
	borders();
}



/*
void Abductor::flee(float dt)
{
_velocity = getPosition() - _targetPosition;
normalize(_velocity);

move(_velocity * _speed * dt);
_orientation = getNewOrientation(_velocity);
setRotation(_orientation);
}
void Abductor::seek(float dt)
{
_velocity = _targetPosition - getPosition();
normalize(_velocity);

move(_velocity * _speed * dt);
_orientation = getNewOrientation(_velocity);
setRotation(_orientation);
}

void Abductor::arrival(float dt)
{
_velocity = _targetPosition - getPosition();
float velocityLenght = lenght(_velocity);

if (velocityLenght > 0)
{
float speed = _speed / _timeToTarget;

if (speed > _speed)
speed = _speed;

normalize(_velocity);

move(_velocity * speed * dt);
_orientation = getNewOrientation(_velocity);
setRotation(_orientation);
}
}
*/

// This file defines the boid class. This includes the attributes found in
// boids -- speed, location on the board, acceleration, etc.
