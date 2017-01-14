#pragma once

#include "GameObject.h"
#include "Projectile.h"
#include "Abductor.h"
#include "Interceptor.h"

class AlienNest : public GameObject
{
public:
							AlienNest(std::vector<Interceptor*>& interceptors, std::vector<Abductor*>& abductors, sf::Texture &interceptorTexture, sf::Texture &abductorTexture);
							~AlienNest();

	void					Initialize(sf::Vector2f position, sf::Texture &texture, sf::FloatRect screenSize);
	void					Update(float dt, sf::Vector2f playerPosition);

	void					TakenDamage();
	void					Die();

	bool					getAlive() const;

private:
	void					FireRateTimer(float dt);
	void					SpawnTimer(float dt);
	void					WonderTimer(float dt);

	void					UpdateBehaviour(sf::Vector2f playerPosition);

	void					Move();

	void					Wonder();
	void					Evade();

	void					CheckBorder();

	void					Shoot(sf::Vector2f playerPosition);
	void					SpawnAbductor();

private:
	sf::Texture&			_interceptorTexture;
	sf::Texture&			_abductorTexture;

	sf::Vector2f			_velocity;
	sf::Vector2u			_screenSize;

	std::vector<Interceptor*>&_interceptors;
	std::vector<Abductor*>&	 _abductors;

	float					_fireRateTimer;
	float					_spawnTimer;
	float					_wonderTimer;

	int						_keepGoingTimes;
	int						_angle;
	int						_lifes;
	int						_rocketsAlive;

	bool					_goClockWise;
	bool					_wondering;
	bool					_isAlive;
	bool					_canFire;
	bool					_canSpawnAbductor;
};

