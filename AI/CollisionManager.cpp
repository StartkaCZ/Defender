#include "CollisionManager.h"
/*
#include "ParticleSystemManager.h"
#include "AudioManager.h"
*/

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

/*
void CollisionManager::CheckForCollisions(Player*& player, std::vector<Projectile*>& projectiles, std::vector<Interceptor*>& interceptors, std::vector<PowerUp*>& powerUps, std::vector<Meteor*>& meteors, std::vector<AlienNest*>& nests)
{
	CheckProjectileCollision(player, projectiles, meteors, nests);
	CheckInterceptorCollision(player, interceptors, meteors);

	CheckMeteorCollision(player, meteors);
	CheckPlayerToPowerUpsCollision(player, powerUps);
}*/

void CollisionManager::CheckForCollisions(std::vector<Region*>& regions)
{
	for (int i = 0; i < regions.size(); i++)
	{
		for (int j = 0; j < regions[i]->getGameObjects().size(); j++)
		{
			for (int k = j + 1; k < regions[i]->getGameObjects().size(); k++)
			{
				if (k != j)
				{
					CollisionBasedOnType(regions[i]->getGameObjects()[j], regions[i]->getGameObjects()[k]);
				}
			}
		}
	}
}

void CollisionManager::CollisionBasedOnType(GameObject*& a, GameObject*& b)
{
	if (Collided(a->getPosition(), a->getSize(), b->getPosition(), b->getSize()))
	{
		a->CollisionEnter(b);
		b->CollisionEnter(a);
	}
}
/*
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
					ParticleSystemManager::Instance()->CreateParticleSystem((nests[j]->getPosition() + projectiles[i]->getPosition()) *0.5f, ParticleSystemManager::ParticleType::PlayerLazer);
					AudioManager::Instance()->PlaySound(AudioManager::SoundType::UnitHit);
					nests[j]->TakenDamage();
					projectiles[i]->Die();
				}
			}
		}
		else if (projectiles[i]->getType() == ObjectType::Projetile_Interceptor)
		{//check enemy projectile to player collision
			if (Collided(player->getPosition(), player->getSize(), projectiles[i]->getPosition(), projectiles[i]->getSize()))
			{
				ParticleSystemManager::Instance()->CreateParticleSystem((player->getPosition() + projectiles[i]->getPosition()) *0.5f, ParticleSystemManager::ParticleType::EnemyLazer);
				AudioManager::Instance()->PlaySound(AudioManager::SoundType::UnitHit);
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
					AudioManager::Instance()->PlaySound(AudioManager::SoundType::UnitHit);
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
		if (interceptor[i]->getType() == ObjectType::Projetile_Interceptor)
		{//check enemy projectile to player collision
			if (Collided(player->getPosition(), player->getSize(), interceptor[i]->getPosition(), interceptor[i]->getSize()))
			{
				ParticleSystemManager::Instance()->CreateParticleSystem((player->getPosition() + interceptor[i]->getPosition()) *0.5f, ParticleSystemManager::ParticleType::EnemyLazer);
				AudioManager::Instance()->PlaySound(AudioManager::SoundType::UnitHit);
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
					AudioManager::Instance()->PlaySound(AudioManager::SoundType::UnitHit);
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
			ParticleSystemManager::Instance()->CreateParticleSystem((player->getPosition() + meteors[i]->getPosition()) *0.5f, ParticleSystemManager::ParticleType::Death);
			AudioManager::Instance()->PlaySound(AudioManager::SoundType::UnitDestroyed);
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
			ParticleSystemManager::Instance()->CreateParticleSystem((player->getPosition() + powerUps[i]->getPosition()) *0.5f, ParticleSystemManager::ParticleType::PowerUp);
			AudioManager::Instance()->PlaySound(AudioManager::SoundType::PowerUpCollected);
			player->CollectedPowerUp(powerUps[i]->getType());
			powerUps[i]->Die();
		}
	}
}*/

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