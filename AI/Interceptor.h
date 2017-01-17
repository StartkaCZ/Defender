#pragma once
#include "Projectile.h"
class Interceptor : public Projectile
{
public:
					Interceptor(int& parentRocketCounter);
					~Interceptor();

	void			initialize(sf::Vector2f position, sf::Texture &texture, sf::Vector2f target, sf::Vector2u screenSize);

	void			Update(float dt, sf::Vector2f playerPosition);
	void			CalculateVelocity(sf::Vector2f playerPosition);

	virtual void	CollisionEnter(GameObject*& objectCollided) override;
	void			Die() override;

private:
	int&			_parentRocketCounter;
};

