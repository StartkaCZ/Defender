#pragma once

#include "Player.h"
#include "PowerUp.h"
#include "Meteor.h"
#include "Projectile.h"
#include "Interceptor.h"
#include "AlienNest.h"
#include "Abductor.h"
#include "Astronaut.h"

#include "Region.h"
#include "Vector2Calculator.h"

#include <vector>

class CollisionManager
{
public:
	static CollisionManager* Instance();

	CollisionManager();
	~CollisionManager();

	void CheckForCollisions(std::vector<Region*>& regions);
	void CollisionBasedOnType(GameObject*& a, GameObject*& b);

	bool Collided(sf::Vector2f p1, sf::Vector2f s1, sf::Vector2f p2, sf::Vector2f s2);

private:
	static CollisionManager* _instance;
};

