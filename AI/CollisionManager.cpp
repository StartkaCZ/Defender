#include "CollisionManager.h"

CollisionManager* CollisionManager::_instance = nullptr;

CollisionManager* CollisionManager::Instance()
{
	if (_instance == nullptr)
	{
		_instance = new CollisionManager();
	}

	return _instance;
}

CollisionManager::CollisionManager()
{
}


CollisionManager::~CollisionManager()
{
}


void CollisionManager::CheckForCollisions(Player*& player, std::vector<Projectile*>& projectiles, std::vector<PowerUp*>& powerUps, std::vector<Meteor*>& meteors)
{
	CheckProjectileCollision(player, projectiles, meteors);

	CheckMeteorCollision(player, meteors);
	CheckPlayerToPowerUpsCollision(player, powerUps);
}

void CollisionManager::CheckProjectileCollision(Player*& player, std::vector<Projectile*>& projectiles, std::vector<Meteor*>& meteors)
{
	for (int i = 0; i < projectiles.size(); i++)
	{
		bool checkFurther = true;

		for (int j = 0; j < meteors.size(); j++)
		{
			if (Collided(projectiles[i]->getPosition(), projectiles[i]->getSize(), meteors[j]->getPosition(), meteors[j]->getSize()))
			{
				checkFurther = false;
				projectiles[i]->Die();
				i++;
				break;
			}
		}

		if (checkFurther)
		{//if this bullet hasn't hit the obstacle, check against other objects
			if (projectiles[i]->getType() == ObjectType::Projetile_PlayerLazer)
			{//check player projectile to enemy collision
				
			}
			else
			{//check enemy projectile to player collision
				if (Collided(player->getPosition(), player->getSize(), projectiles[i]->getPosition(), projectiles[i]->getSize()))
				{
					player->TakenDamage();
					projectiles[i]->Die();
				}
			}
		}
	}
}
void CollisionManager::CheckMeteorCollision(Player*& player, std::vector<Meteor*>& meteors)
{
	for (int i = 0; i < meteors.size(); i++)
	{
		if (Collided(player->getPosition(), player->getSize(), meteors[i]->getPosition(), meteors[i]->getSize()))
		{
			player->TakenDamage();
			meteors[i]->Die();
		}
	}
}
void CollisionManager::CheckPlayerToPowerUpsCollision(Player*& player, std::vector<PowerUp*>& powerUps)
{
	for (int i = 0; i < powerUps.size(); i++)
	{
		if (Collided(player->getPosition(), player->getSize(), powerUps[i]->getPosition(), powerUps[i]->getSize()))
		{
			player->CollectedPowerUp(powerUps[i]->getType());
			powerUps[i]->Die();
		}
	}
}

bool CollisionManager::Collided(sf::Vector2f p1, sf::Vector2f s1, sf::Vector2f p2, sf::Vector2f s2)
{
	bool collided = true;

	if (p1.x + s1.x < p2.x - s2.x || p1.x - s1.x > p2.x + s2.x ||
		p1.y + s1.y < p2.y - s2.y || p1.y - s1.y > p2.y + s2.y)
	{
		collided = false;
	}

	return collided;
}