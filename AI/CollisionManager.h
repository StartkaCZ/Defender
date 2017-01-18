#pragma once

#include "Player.h"
#include "PowerUp.h"
#include "Meteor.h"
#include "Projectile.h"
#include "Interceptor.h"
#include "AlienNest.h"
#include "Abductor.h"
#include "Astronaut.h"

#include "Vector2Calculator.h"
#include <vector>

class CollisionManager
{
public:
	static CollisionManager* Instance();

	CollisionManager();
	~CollisionManager();

	void CheckForCollisions(Player*& player, std::vector<Projectile*>& projectiles, std::vector<Interceptor*>& interceptor, std::vector<PowerUp*>& powerUps, std::vector<Meteor*>& meteors, std::vector<AlienNest*>& nests, std::vector<Abductor*>& abductors, std::vector<Astronaut*> astronauts);

	void CheckProjectileCollision(Player*& player, std::vector<Projectile*>& projectiles, std::vector<Meteor*>& meteors, std::vector<AlienNest*>& nests, std::vector<Abductor*>& abductors, std::vector<Astronaut*> astronauts);
	void CheckInterceptorCollision(Player*& player, std::vector<Interceptor*>& interceptor, std::vector<Meteor*>& meteors);
	void CheckMeteorCollision(Player*& player, std::vector<Meteor*>& meteors);

	void CheckPlayerToPowerUpsCollision(Player*& player, std::vector<PowerUp*>& powerUps);

	void CheckAbductorCollision(Player*& player, std::vector<Abductor*>& abductors);

	bool Collided(sf::Vector2f p1, sf::Vector2f s1, sf::Vector2f p2, sf::Vector2f s2);

private:
	static CollisionManager* _instance;
};

