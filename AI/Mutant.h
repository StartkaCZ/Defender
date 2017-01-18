#ifndef Mutant_H
#define Mutant_H

#include <vector>

#include "GameObject.h"
#include "Pvector.h"
#include "SFML/Graphics.hpp"
#include "Astronaut.h"
#include "Bullet.h"
#include "Mutant.h"

class Mutant : public GameObject
{
private:
	enum class State;
	State					_state;
	sf::Texture&			_bulletTexture;
	std::vector<Bullet*>&	_bullets;

	int						_lifes;

	bool					_canFire;
	float					_fireRateTimer;

	bool					_isAlive;
	sf::Vector2u			_screenSize;
	
	Pvector					_velocity;
	Pvector					_acceleration;
	float					_maxSpeed;
	float					_maxForce;
	Pvector					_location;

	void					FireRateTimer(float dt);
	
	void					applyForce(Pvector force);

public:
	
	enum class State
	{
		seek,
		swarm,
	};


	Mutant(std::vector<Bullet*>& bullets, sf::Texture &bulletTexture);
	~Mutant();

	void					initialize(sf::Vector2f position, sf::Texture &texture, sf::FloatRect);

	void					update(float dt);
	void					swarm(vector <Mutant*> v, sf::Vector2f);
	void					seek(sf::Vector2f p);

	void					borders();
	void					Shoot(sf::Vector2f playerPosition);
	sf::Vector2f			getFireDirection(sf::Vector2f playerPosition);
	void					TakenDamage();
	void					Die();
	bool					getAlive();

	State					getState();
	void					setState(State state);

	Pvector					getLocation();
	void					setLocation(Pvector);

	bool					getCanFire();
	void					setCanFire(bool);
};

#endif // Abductor_H