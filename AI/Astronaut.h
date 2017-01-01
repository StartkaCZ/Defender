#pragma once

#include "GameObject.h"
#include <map>
class Astronaut : public GameObject
{
private:
	enum class state {
		 walk,
		 capture,
		 fall
	};
	state _state;
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
public:
	Astronaut()
	{
		
		//_sprite.setTextureRect(sf::IntRect(0, 0, FRAME_PIXEL_WIDTH, FRAME_PIXEL_HEIGHT));
		_direction = rand() % 2;
		if (!_direction)
			_direction = -1;

		_speed = 50 + rand() % 10;
		_state = state::fall;
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
		case(state::walk):
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
		case(state::capture):
			//_sprite.setTextureRect(sf::IntRect(FRAME_PIXEL_WIDTH * _currentFrame, 0, FRAME_PIXEL_WIDTH, FRAME_PIXEL_HEIGHT));
			break;
		default: // case(state::fall):
			position = getPosition();
			position.y += GRAVITY * deltatime;
			setPosition(position);
			if (position.y > GROUND_LEVEL) {
				_state = state::walk;

			}
			break;
		}
	}
	~Astronaut()
	{

	}

};

