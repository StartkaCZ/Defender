#ifndef ALIEN_H
#define ALIEN_H

#include <SFML/Graphics.hpp>

class Alien : public sf::Drawable, private sf::NonCopyable, private sf::Transformable
{
public:
	void					initialize(sf::Vector2f position, sf::Texture &texture, sf::Vector2u screenSize, bool flee);
	void					update(float dt, sf::Vector2f playerPosition);

private:
	void					flee(float dt);
	void					seek(float dt);

	void					arrival(float dt);

	void					normalize(sf::Vector2f &vector);
	
	float					lenght(const sf::Vector2f &a);
	float					distance(sf::Vector2f a, sf::Vector2f b);
	float					getNewOrientation(const sf::Vector2f &source);

	virtual void			draw(sf::RenderTarget& target, sf::RenderStates states) const;


private:
	sf::Sprite				_sprite;
	sf::Vector2f			_velocity;
	sf::Vector2u			_screenSize;

	sf::Vector2f			_targetPosition;

	float					_speed;
	float					_orientation;
	float					_timeToTarget;

	bool					_flee;

	sf::Keyboard::Key		_left;
	sf::Keyboard::Key		_right;
	sf::Keyboard::Key		_down;
	sf::Keyboard::Key		_up;

	const float				SPEED = 200.0f;
	const float				PI = 3.141592;
};

#endif // ALIEN_H