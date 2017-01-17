#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"
#include "Projectile.h"

class Player : public GameObject
{
public:
							Player(std::vector<Projectile*>& projectiles, sf::Texture &lazerTexture);

	void					Initialize(sf::Vector2f position, sf::Texture &texture, sf::FloatRect screenSize);
	void					Update(float dt);
	void					ReadInput();

	void					NukingOver();

	void					CollectedPowerUp(ObjectType powerUp);
	virtual void			CollisionEnter(GameObject*& objectCollided) override;
	void					TakenDamage();

	bool					hasNuked();


private:
	void					FireRateTimer(float dt);
	void					NukeTimer(float dt);
	void					SuperJumpTimer(float dt);
	void					ShieldTimer(float dt);
	void					RapidFireTimer(float dt);
	
	void					MoveLeft();
	void					MoveRight();
	void					MoveUp();
	void					MoveDown();

	void					Decelerate();
	void					StopVerticalMovement();

	void					Shoot();
	void					Nuke();
	void					SuperJump();

private:
	sf::Texture&			_lazerTexture;
	
	sf::Vector2f			_velocity;
	sf::Vector2u			_screenSize;

	std::vector<Projectile*>&_projectiles;

	float					_fireRateTimer;
	float					_nukeTimer;
	float					_superJumpTimer;
	float					_shieldTimer;
	float					_rapidFireTimer;

	int						_nukeCount;
	int						_superJumpCount;
	int						_lifes;

	bool					_canFire;
	bool					_canNuke;
	bool					_canSuperJump;

	bool					_hasNuked;
	bool					_movingLeft;
	bool					_rapidFire;
	bool					_shieldOn;
};

#endif // PLAYER_H
