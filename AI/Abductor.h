#ifndef Abductor_H
#define Abductor_H

#include <vector>

#include "GameObject.h"
#include "Pvector.h"
#include "SFML/Graphics.hpp"
#include "Astronaut.h"
#include "Bullet.h"
#include "Mutant.h"

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
	sf::Vector2u			_screenSize;
	bool					predator;
	Pvector					location;
	Pvector					velocity;
	Pvector					acceleration;
	float					maxSpeed;
	float					maxForce;


	void					FireRateTimer(float dt);
	void					Shoot(sf::Vector2f playerPosition);
	void					applyForce(Pvector force);
	Pvector					Separation(vector<Abductor*> Boids, sf::Vector2f playerPos);
	Pvector					Alignment(vector<Abductor*> Boids);
	Pvector					Cohesion(vector<Abductor*> Boids);

public:
	enum class State
	{
		flock,
		seek,
		flee,
	};


							Abductor(std::vector<Bullet*>& bullets, sf::Texture &bulletTexture);
							~Abductor();

	void					initialize(sf::Vector2f position, sf::Texture &texture, sf::FloatRect);
	Pvector					seek(Pvector v);
	
	void					update(float dt, sf::Vector2f playerPosition);
	void					flock(vector <Abductor*> v, sf::Vector2f playerPos);
	void					swarm(vector <Abductor*> v);
	void					findAstronaut(Astronaut* astro);
	void					seek();
	bool					flee(sf::Vector2f);
	void					borders();

	void					TakenDamage();
	void					Die();
	bool					getAlive();
	Astronaut*				getTarget();
	State					getState();
	void					setState(State state);
	void					setTargetPosOffset(sf::Vector2f targetPosOffset);
};

#endif // Abductor_H