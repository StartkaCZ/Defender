#pragma once

#include "GameObject.h"
#include <map>
#include "Vector2Calculator.h"

class Astronaut : public GameObject
{
private:
	const int			FRAME_PIXEL_WIDTH = 64;
	const int			FRAME_PIXEL_HEIGHT = 128.0f;
	const int			MAX_FRAME_WIDTH = 3;
	const float			GRAVITY = 100.0f;
	

	enum class State;
	State				_state;
	int					_direction;
	int					_speed;

	float				_animationtimer;
	int					_currentFrame;
	float				_animationRate;

	sf::Vector2u		_screenSize;

	int					_lifes;
	bool				_isAlive;	
	bool				_isTarget;
	bool				_isRunning;

public:

	enum class State 
	{
		walk,
		capture,
		fall
	};

public:
						Astronaut();
						~Astronaut();

	void				Initialize(sf::Vector2f position, sf::Texture &texture, sf::FloatRect screenSize);
	void				update(float deltatime);

	bool				getIsRunning();
	void				setIsRunning(bool _isRunning);

	float				getSpeed();
	void				setSpeed(float speed);

	int					getDirection();
	void				setDirection(int direction);

	bool				getAlive();

	void				TakenDamage();
	void				Die();


	State				getState();
	void				setState(State state);



	bool				getIsTarget();
	void				setIsTarget(bool target);
};

