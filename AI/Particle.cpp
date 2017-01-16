#include "Particle.h"

Particle::Particle(float timer, sf::Vector2f dir, float speed, sf::Vector2f position, sf::Texture& texture)
	: _timer(timer)
	, _startTimer(timer)
	, _alive(true)
	, _velocity(dir * speed)
{
	_sprite.setTexture(texture);
	_sprite.setOrigin(sf::Vector2f(_sprite.getTextureRect().width, _sprite.getTextureRect().height));
	_sprite.setScale(0.25f, 0.25f);
	_sprite.setPosition(position);
}

void Particle::Update(float dt)
{
	_sprite.move(_velocity * dt);
	_sprite.rotate(10);

	if (_timer <= 0)
	{
		_alive = false;
	}
	else
	{
		_timer -= dt;
		sf::Color colour = _sprite.getColor();
		colour.a = ALPHA * (_timer / _startTimer);
		_sprite.setScale(0.25f * (_timer / _startTimer), 0.25f * (_timer / _startTimer));
		_sprite.setColor(colour);
	}
}

void Particle::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_sprite, states);
}

bool Particle::isAlive() const
{
	return _alive;
}