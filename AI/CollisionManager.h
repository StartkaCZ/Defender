#pragma once

#include "Player.h"
#include "PowerUp.h"
#include "Meteor.h"
#include "Projectile.h"
#include "Interceptor.h"
#include "AlienNest.h"

#include "Region.h"

#include <vector>

class CollisionManager
{
public:
	static CollisionManager* Instance();

	CollisionManager();
	~CollisionManager();

	//void CheckForCollisions(Player*& player, std::vector<Projectile*>& projectiles, std::vector<Interceptor*>& interceptor, std::vector<PowerUp*>& powerUps, std::vector<Meteor*>& meteors, std::vector<AlienNest*>& nests);
	void CheckForCollisions(std::vector<Region*>& regions);
	void CollisionBasedOnType(GameObject*& a, GameObject*& b);
/*
	void CheckProjectileCollision(Player*& player, std::vector<Projectile*>& projectiles, std::vector<Meteor*>& meteors, std::vector<AlienNest*>& nests);
	void CheckInterceptorCollision(Player*& player, std::vector<Interceptor*>& interceptor, std::vector<Meteor*>& meteors);
	void CheckMeteorCollision(Player*& player, std::vector<Meteor*>& meteors);

	void CheckPlayerToPowerUpsCollision(Player*& player, std::vector<PowerUp*>& powerUps);
	*/
	bool Collided(sf::Vector2f p1, sf::Vector2f s1, sf::Vector2f p2, sf::Vector2f s2);

private:
	static CollisionManager* _instance;
};

