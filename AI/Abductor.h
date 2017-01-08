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

using namespace std;


class Abductor : public GameObject
{
private:

	Astronaut* _target;
public:

	enum class state
	{
		flock,
		attack,
		flee
	};
	state _state;

	sf::Vector2u _screenSize;
	bool predator;
	Pvector location;
	Pvector velocity;
	Pvector acceleration;
	float maxSpeed;
	float maxForce;

	Abductor() {};
	Abductor( float x, float y) : _target(NULL), _state(state::flock)
	{
		acceleration = Pvector(0, 0);
		velocity = Pvector(rand() % 3 - 2, rand() % 3 - 2); // Allows for range of -2 -> 2
		location = Pvector(x, y);
		maxSpeed = 3.5;
		maxForce = 0.5;
	}
	Abductor(float x, float y, bool predCheck) : _state(state::flock)
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
	}
	void initialize(sf::Vector2f position, sf::Texture &texture, sf::FloatRect);
	void update(float dt, sf::Vector2f playerPosition);
	/*
	Destructors are commented out for now. g++ throws errors if they are included.
	If compiling on Visual Studio, however, no errors are thrown.
	//Destructor
	Boid::~Boid()
	{
	//cout << "Boid is being deleted by destructor!" << endl;
	}
	*/
	void applyForce(Pvector force);
	// Three Laws that boids follow
	Pvector Separation(vector<Abductor*> &Boids);
	Pvector Alignment(vector<Abductor*> &Boids);
	Pvector Cohesion(vector<Abductor*> &Boids);
	//Functions involving SFML and visualisation linking
	Pvector seek(Pvector v);
	void run(vector <Abductor*> &v, Astronaut* astro);
	void update();
	void flock(vector <Abductor*> &v);
	void borders();
	float angle(Pvector v);
	void swarm(vector <Abductor*> &v);
};

#endif // Abductor_H