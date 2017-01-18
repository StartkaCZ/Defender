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