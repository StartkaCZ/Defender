#pragma once

#include "GameObject.h"
#include "Projectile.h"
#include "Abductor.h"

class AlienNest : public GameObject
{
public:
							AlienNest(std::vector<Projectile*>& projectiles, std::vector<Abductor*>& abductors);
							~AlienNest();

	void					Initialize(sf::Vector2f position, sf::Texture &texture, sf::Texture &lazerTexture, sf::Texture &abductorTexture, sf::FloatRect screenSize);
	void					Update(float dt, sf::Vector2f playerPosition);

	void					TakenDamage();
	void					Die();

	bool					getAlive() const;

private:
	void					FireRateTimer(float dt);
	void					SpawnTimer(float dt);

	void					UpdateStatus(sf::Vector2f playerPosition);
	void					Move(float dt);
	void					Wonder();
	void					Evade();
	void					CheckBorder();

	void					Shoot();
	void					SpawnAbductor();

private:
	sf::Texture				_lazerTexture;
	sf::Texture				_abductorTexture;

	sf::Vector2f			_targetPosition;
	sf::Vector2f			_velocity;
	sf::Vector2u			_screenSize;

	std::vector<Projectile*>&_projectiles;
	std::vector<Abductor*>&	 _abductors;

	float					_fireRateTimer;
	float					_spawnTimer;

	int						_lifes;
	int						_rocketsAlive;

	bool					_wondering;
	bool					_isAlive;
	bool					_canFire;
	bool					_canSpawnAbductor;
};

