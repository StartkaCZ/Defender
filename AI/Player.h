#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

class Player : public sf::Drawable, private sf::NonCopyable, private sf::Transformable
{
public:
	void					initialize(sf::Vector2f position, sf::Texture &texture, sf::Keyboard::Key left, sf::Keyboard::Key right, sf::Keyboard::Key down, sf::Keyboard::Key up, sf::Vector2u screenSize);
	void					update(float dt);
	void					readInput();

	sf::Vector2f			position();


private:
	virtual void			draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void					orientate(bool left);


private:
	sf::Sprite				_sprite;
	sf::Vector2f			_velocity;
	sf::Vector2u			_screenSize;

	float					_speed;
	float					_orientation;

	sf::Keyboard::Key		_left;
	sf::Keyboard::Key		_right;
	sf::Keyboard::Key		_down;
	sf::Keyboard::Key		_up;

	const float				ROTATION = 3.0f;
	const float				SPEED = 500.0f;
	const float				PI = 3.141592;
};

#endif // PLAYER_H
