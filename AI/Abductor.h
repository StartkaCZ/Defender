#ifndef Abductor_H
#define Abductor_H

#include "GameObject.h"

class Abductor : public GameObject
{
public:
							Abductor();
							~Abductor();

	void					initialize(sf::Vector2f position, sf::Texture &texture, sf::FloatRect screenSize);
	void					update(float dt, sf::Vector2f playerPosition);

private:
	/*
	void					flee(float dt);
	void					seek(float dt);

	void					arrival(float dt);

	void					normalize(sf::Vector2f &vector);
	
	float					lenght(const sf::Vector2f &a);
	float					distance(sf::Vector2f a, sf::Vector2f b);
	float					getNewOrientation(const sf::Vector2f &source);
	*/


private:
	sf::Vector2f			_velocity;
	sf::Vector2u			_screenSize;

	sf::Vector2f			_targetPosition;

	float					_speed;
	float					_orientation;
	float					_timeToTarget;

	bool					_flee;
};

#endif // Abductor_H