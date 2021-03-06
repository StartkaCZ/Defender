#pragma once

#include "GameObject.h"
#include "Projectile.h"
#include "Abductor.h"
#include "Interceptor.h"
#include "Meteor.h"
#include "Bullet.h"


class AlienNest : public GameObject
{
public:
							AlienNest(std::vector<Interceptor*>& interceptors, std::vector<Abductor*>& abductors, std::vector<Bullet*>& abductorBullets, sf::Texture &interceptorTexture, sf::Texture &abductorTexture, sf::Texture &abductorBulletTexture);
							~AlienNest();

	void					Initialize(sf::Vector2f position, sf::Texture &texture, sf::FloatRect screenSize);
	void					Update(float dt, sf::Vector2f playerPosition, std::vector<Meteor*>& meteors);

	virtual void			CollisionEnter(GameObject*& objectCollided) override;
	void					TakenDamage();
	void					Die();

private:
	void					FireRateTimer(float dt);
	void					SpawnTimer(float dt);
	void					WonderTimer(float dt);

	void					UpdateBehaviour(sf::Vector2f playerPosition);

	void					Move();

	void					Orientate(int rotateBy, int angleToAdd);
	void					NormalizeAngle();

	void					AvoidMeteors(std::vector<Meteor*>& meteors);

	void					CheckBorder();

	void					Shoot(sf::Vector2f playerPosition);
	void					SpawnAbductor();

private:
	sf::Texture&			_interceptorTexture;
	sf::Texture&			_abductorTexture;
	sf::Texture&			_abductorBulletTexture;

	sf::Vector2f			_velocity;
	sf::Vector2u			_screenSize;

	std::vector<Interceptor*>&_interceptors;
	std::vector<Abductor*>&	 _abductors;
	std::vector<Bullet*>&	 _abductorbullets;
	float					_fireRateTimer;
	float					_spawnTimer;
	float					_wonderTimer;

	int						_keepGoingTimes;
	int						_angle;
	int						_lifes;
	int						_rocketsAlive;

	bool					_goClockWise;
	bool					_wondering;
	bool					_canFire;
	bool					_canSpawnAbductor;
};

