#include "CollisionManager.h"

#include "ParticleSystemManager.h"
#include "AudioManager.h"


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


void CollisionManager::CheckForCollisions(Player*& player, std::vector<Projectile*>& projectiles, std::vector<Interceptor*>& interceptors, std::vector<PowerUp*>& powerUps, std::vector<Meteor*>& meteors, std::vector<AlienNest*>& nests)
{
	CheckProjectileCollision(player, projectiles, meteors, nests);
	CheckInterceptorCollision(player, interceptors, meteors);

	CheckMeteorCollision(player, meteors);
	CheckPlayerToPowerUpsCollision(player, powerUps);
}

void CollisionManager::CheckProjectileCollision(Player*& player, std::vector<Projectile*>& projectiles, std::vector<Meteor*>& meteors, std::vector<AlienNest*>& nests)
{
	for (int i = 0; i < projectiles.size(); i++)
	{
		if (projectiles[i]->getType() == ObjectType::Projetile_PlayerLazer)
		{//check player projectile to enemy collision
			for (int j = 0; j < nests.size(); j++)
			{
				if (Collided(nests[j]->getPosition(), nests[j]->getSize(), projectiles[i]->getPosition(), projectiles[i]->getSize()))
				{
					nests[j]->TakenDamage();
					projectiles[i]->Die();
				}
			}
		}
		else if (projectiles[i]->getType() == ObjectType::Projetile_Interceptor)
		{//check enemy projectile to player collision
			if (Collided(player->getPosition(), player->getSize(), projectiles[i]->getPosition(), projectiles[i]->getSize()))
			{
				player->TakenDamage();
				projectiles[i]->Die();
			}
		}
		else
		{
			for (int j = 0; j < meteors.size(); j++)
			{
				if (Collided(projectiles[i]->getPosition(), projectiles[i]->getSize(), meteors[j]->getPosition(), meteors[j]->getSize()))
				{
					projectiles[i]->Die();
					i++;
					break;
				}
			}
		}	
	}
}
void CollisionManager::CheckInterceptorCollision(Player*& player, std::vector<Interceptor*>& interceptor, std::vector<Meteor*>& meteors)
{
	for (int i = 0; i < interceptor.size(); i++)
	{
		if (interceptor[i]->getType() == ObjectType::Projetile_PlayerLazer)
		{//check player projectile to enemy collision

		}
		else if (interceptor[i]->getType() == ObjectType::Projetile_Interceptor)
		{//check enemy projectile to player collision
			if (Collided(player->getPosition(), player->getSize(), interceptor[i]->getPosition(), interceptor[i]->getSize()))
			{
				player->TakenDamage();
				interceptor[i]->Die();
			}
		}
		else
		{
			for (int j = 0; j < meteors.size(); j++)
			{
				if (Collided(interceptor[i]->getPosition(), interceptor[i]->getSize(), meteors[j]->getPosition(), meteors[j]->getSize()))
				{
					interceptor[i]->Die();
					i++;
					break;
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