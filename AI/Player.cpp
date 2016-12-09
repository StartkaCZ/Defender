#include "Player.h"

void Player::initialize(sf::Vector2f position, sf::Texture &texture, sf::Keyboard::Key left, sf::Keyboard::Key right, sf::Keyboard::Key down, sf::Keyboard::Key up, sf::Vector2u screenSize)
{
	_left = left;
	_right = right;
	_down = down;
	_up = up;

	_screenSize = screenSize;

	_sprite = sf::Sprite();
	_sprite.setTexture(texture);
	setPosition(position);

	_speed = SPEED;
	
	_velocity = sf::Vector2f(rand() % 3 - 1, rand() % 3 - 1);

	while (_velocity.x == 0 && _velocity.y == 0)
	{
		_velocity = sf::Vector2f(rand() % 3 - 1, rand() % 3 - 1);
	}

	_sprite.setOrigin(texture.getSize().x * 0.5f, texture.getSize().y * 0.5f);
	_orientation = atan2(_velocity.y, _velocity.x) * 180 / PI;
	setRotation(_orientation);
	_velocity = sf::Vector2f(cos(_orientation * PI / 180), sin(_orientation * PI / 180));
}

void Player::update(float dt)
{
	move(_velocity * _speed * dt);
	setRotation(_orientation);

	if (getPosition().x > _screenSize.x)
		setPosition(0, getPosition().y);
	else if (getPosition().y > _screenSize.y)
		setPosition(getPosition().x, 0);

	if (getPosition().x < 0)
		setPosition(_screenSize.x, getPosition().y);
	else if (getPosition().y < 0)
		setPosition(getPosition().x, _screenSize.y);
}

void Player::readInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		_speed += 25.0f;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		_speed -= 25.0f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		orientate(true);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		orientate(false);
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// Apply transform of current node
	states.transform *= getTransform();
	target.draw(_sprite, states);
}

void Player::orientate(bool left)
{
	if (left)
		_orientation -= ROTATION;
	else
		_orientation += ROTATION;

	_velocity = sf::Vector2f(cos(_orientation * PI / 180), sin(_orientation * PI / 180));
	setRotation(_orientation);
}


sf::Vector2f Player::position()
{
	return getPosition();
}