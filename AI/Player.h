#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"
#include "Projectile.h"

class Player : public GameObject
{
public:
							Player(std::vector<Projectile*>& projectiles);

	void					initialize(sf::Vector2f position, sf::Texture &texture, sf::FloatRect screenSize);
	void					update(float dt);
	void					readInput();

	sf::Vector2f			position();


private:
	virtual void			draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void					FireRateTimer(float dt);
	void					NukeTimer(float dt);
	void					SuperJumpTimer(float dt);

	void					CheckBorder();
	
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
	sf::Vector2f			_velocity;
	sf::Vector2u			_screenSize;
	sf::Vector2f			_size;

	std::vector<Projectile*>&_projectiles;

	float					_fireRateTimer;
	float					_nukeTimer;
	float					_superJumpTimer;

	int						_nukeCount;
	int						_superJumpCount;

	bool					_canFire;
	bool					_canNuke;
	bool					_canSuperJump;
};

#endif // PLAYER_H
