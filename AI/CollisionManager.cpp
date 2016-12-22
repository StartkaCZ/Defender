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


void CollisionManager::CheckForCollisions()
{

}