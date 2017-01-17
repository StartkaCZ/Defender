#ifndef Abductor_H
#define Abductor_H



#include <vector>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <math.h>

#include "GameObject.h"
#include "Pvector.h"
#include "SFML/Graphics.hpp"
#include "Astronaut.h"
#include "Bullet.h"
#include "Mutant.h"
using namespace std;


class Abductor : public GameObject
{
private:
	enum class State;
	State					_state;
	Astronaut*				_target;
	sf::Texture&			_bulletTexture;
	std::vector<Bullet*>&	_bullets;

	sf::Vector2f			_targetPosOffset;

	int						_lifes;

	bool					_canFire;
	float					_fireRateTimer;

	bool					_isAlive;
	
public:
	enum class State
	{
		flock,
		seek,
		flee,
	};

	sf::Vector2u _screenSize;
	bool predator;
	Pvector location;
	Pvector velocity;
	Pvector acceleration;
	float maxSpeed;
	float maxForce;

	Abductor(std::vector<Bullet*>& bullets, sf::Texture &bulletTexture) 
		: _target(nullptr), _state(State::flock), _bullets(bullets), _bulletTexture(bulletTexture), _lifes(1), _isAlive(true), _canFire(true)
	{
	}
	/*
	Abductor(float x, float y, bool predCheck) : _state(State::flock)
	{
		predator = predCheck;
		if (predCheck == true) {
			maxSpeed = 7.5;
			maxForce = 0.5;
			velocity = Pvector(rand() % 3 - 1, rand() % 3 - 1);
		}
		else {
			maxSpeed = 3.5;
			maxForce = 0.5;
			velocity = Pvector(rand() % 3 - 2, rand() % 3 - 2); // Allows for range of -2 -> 2
		}
		acceleration = Pvector(0, 0);
		location = Pvector(x, y);
	}*/
	void initialize(sf::Vector2f position, sf::Texture &texture, sf::FloatRect);
	
	/*
	Destructors are commented out for now. g++ throws errors if they are included.
	If compiling on Visual Studio, however, no errors are thrown.
	//Destructor
	Boid::~Boid()
	{
	//cout << "Boid is being deleted by destructor!" << endl;
	}
	*/
	void FireRateTimer(float dt);
	void Shoot(sf::Vector2f playerPosition);
	void applyForce(Pvector force);
	// Three Laws that boids follow
	Pvector Separation(vector<Abductor*> Boids, sf::Vector2f playerPos);
	Pvector Alignment(vector<Abductor*> Boids);
	Pvector Cohesion(vector<Abductor*> Boids);
	//Functions involving SFML and visualisation linking
	Pvector seek(Pvector v);
	void update(float dt, sf::Vector2f playerPosition);
	void flock(vector <Abductor*> v, sf::Vector2f playerPos);
	void borders();
	float angle(Pvector v);
	void swarm(vector <Abductor*> v);

	bool findAstronaut(Astronaut* astro);
	void seek();
	bool flee();



	void TakenDamage()
	{
		_lifes--;

		if (_lifes == 0)
		{
			Die();
		}
	}

	void Die()
	{
		_isAlive = false;
		if (_target != nullptr)
		{
			_target->setIsTarget(false);
			_target->setState(Astronaut::State::fall);
			_target = nullptr;
		}
	}

	bool getAlive()
	{
		return _isAlive;
	}

	Astronaut* getTarget() {
		return _target;
	}

	State getState() {
		return _state;
	}
	void setState(State state) {
		_state = state;
	}

	void setTargetPosOffset(sf::Vector2f targetPosOffset)
	{
		_targetPosOffset = targetPosOffset;
	}
};

#endif // Abductor_H