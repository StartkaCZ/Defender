#pragma once

#include <vector>

class CollisionManager
{
public:
	static CollisionManager* Instance();

	CollisionManager();
	~CollisionManager();

	void CheckForCollisions();

private:
	static CollisionManager* _instance;
};

