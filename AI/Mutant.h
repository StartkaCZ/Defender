#ifndef Mutant_H
#define Mutant_H



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
using namespace std;


class Mutant : public GameObject
{
private:
	enum class State;
	State					_state;
	sf::Texture&			_bulletTexture;
	std::vector<Bullet*>&	_bullets;


	sf::Vector2f			_targetPosOffset;
	bool					_canFire;
	float					_fireRateTimer;

	int _lifes;
	int _isAlive;

public:
	enum class State
	{
		flock,
		swarm,
		attack,
		retreat
	};

	sf::Vector2u _screenSize;
	bool predator;
	Pvector location;
	Pvector velocity;
	Pvector acceleration;
	float maxSpeed;
	float maxForce;

	Mutant(std::vector<Bullet*>& bullets, sf::Texture &bulletTexture)
		:  _state(State::flock), _bullets(bullets), _bulletTexture(bulletTexture), _lifes(1), _isAlive(true), _canFire(true), _fireRateTimer(0)
	{
	}

	void Initialize(sf::Vector2f position, sf::Texture &texture, sf::FloatRect);

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
	Pvector Separation(vector<Mutant*> &Boids);
	Pvector Alignment(vector<Mutant*> &Boids);
	Pvector Cohesion(vector<Mutant*> &Boids);
	//Functions involving SFML and visualisation linking
	Pvector seek(Pvector v);
	void update(float dt, sf::Vector2f playerPosition);
	void flock(vector <Mutant*> &v);
	void borders();
	float angle(Pvector v);
	void swarm(vector <Mutant*> &v);
	void flee();
	void evolve();

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