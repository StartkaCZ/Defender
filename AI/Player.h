#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"

class Player : public GameObject
{
public:
	void					initialize(sf::Vector2f position, sf::Texture &texture, sf::Keyboard::Key left, sf::Keyboard::Key right, sf::Keyboard::Key down, sf::Keyboard::Key up, sf::Keyboard::Key shoot, sf::Vector2u screenSize);
	void					update(float dt);
	void					readInput();

	sf::Vector2f			position();


private:
	virtual void			draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void					CheckBorder();
	
	void					MoveLeft();
	void					MoveRight();
	void					MoveUp();
	void					MoveDown();

	void					Decelerate();
	void					StopVerticalMovement();

	void					Shoot();

private:
	sf::Vector2f			_velocity;
	sf::Vector2u			_screenSize;
	sf::Vector2f			_size;

	sf::Keyboard::Key		_left;
	sf::Keyboard::Key		_right;
	sf::Keyboard::Key		_down;
	sf::Keyboard::Key		_up;
	sf::Keyboard::Key		_shoot;
};

#endif // PLAYER_H
