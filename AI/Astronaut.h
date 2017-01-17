#pragma once

#include "GameObject.h"
#include <map>
class Astronaut : public GameObject
{
private:
	enum class State;
	State _state;
	//action
	int _direction;
	int _speed;
	const float GRAVITY = 100.0f;
	const int GROUND_LEVEL = 450;
	//animation
	float _animationtimer;
	int _currentFrame;
	const int FRAME_PIXEL_WIDTH = 100;
	const int FRAME_PIXEL_HEIGHT = 100;
	const int MAX_FRAME_WIDTH = 2;
	const float ANIMATION_RATE = 2.0f;

	bool _isAlive;

	bool _isTarget;

public:
	enum class State {
		walk,
		run,
		capture,
		fall
	};
	Astronaut() : _state(State::fall), _isTarget(false), _isAlive(true)
	{
		//_sprite.setTextureRect(sf::IntRect(0, 0, FRAME_PIXEL_WIDTH, FRAME_PIXEL_HEIGHT));
		_direction = rand() % 2;
		if (!_direction)
			_direction = -1;

		_speed = 50 + rand() % 10;
		_state = State::fall;
	}

	void Initialize(sf::Vector2f position, sf::Texture &texture)
	{
		GameObject::initialize(position, texture, ObjectType::Astronaut);
		_sprite.setScale(0.7f, 0.7f);
	}

	void update(float deltatime) 
	{
		sf::Vector2f position;
		switch (_state)
		{
		case(State::walk):
			//action
			position = getPosition();
			position.x += _speed * deltatime * _direction;
			setPosition(position);
			//aniamtion
			_animationtimer -= deltatime;
			if (_animationtimer < 0){
				_animationtimer = ANIMATION_RATE;
				_currentFrame++;
				if (_currentFrame > MAX_FRAME_WIDTH)
					_currentFrame = 0;		
			}		
			//_sprite.setTextureRect(sf::IntRect(FRAME_PIXEL_WIDTH * _currentFrame,0, FRAME_PIXEL_WIDTH, FRAME_PIXEL_HEIGHT));
			break;
		case(State::capture):
			//_sprite.setTextureRect(sf::IntRect(FRAME_PIXEL_WIDTH * _currentFrame, 0, FRAME_PIXEL_WIDTH, FRAME_PIXEL_HEIGHT));
			break;
		default: // case(state::fall):
			position = getPosition();
			position.y += GRAVITY * deltatime;
			setPosition(position);
			if (position.y > GROUND_LEVEL) {
				_state = State::walk;

			}
			break;
		}
	}
	~Astronaut()
	{

	}
	bool getAlive()
	{
		return _isAlive;
	}

	void Die()
	{
		_isAlive = false;
	}


	State getState() {
		return _state;
	}
	void setState(State state) {
		_state = state;
	}



	bool getIsTarget() {
		return _isTarget;
	}
	void setIsTarget(bool target) {
		_isTarget = target;
	}
};

