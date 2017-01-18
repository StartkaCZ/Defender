#pragma once

#include "GameObject.h"

class PowerUp : public GameObject
{
public:
					PowerUp();
					~PowerUp();

	void			Initialize(sf::Texture &texture, ObjectType type, sf::FloatRect screenRectangle);
	void			Update(float dt);

	virtual void	CollisionEnter(GameObject*& objectCollided) override;
	void			Die();
};

