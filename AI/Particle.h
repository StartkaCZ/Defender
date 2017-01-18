#ifndef PARTICLE_H
#define PARTICLE_H

#include <SFML/Graphics.hpp>

class Particle : public sf::Drawable, protected sf::NonCopyable
{
public:
						Particle(float timer, sf::Vector2f dir, float speed, float initialAlpha, sf::Vector2f position, sf::Texture& texture);

	void				Update(float dt);

	bool				isAlive() const;

protected:
	void				draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	float				_timer;
	float				_startTimer;
	float				_initialAlpha;
	bool				_alive;
	
	sf::Sprite			_sprite;
	sf::Vector2f		_velocity;

	const float			SCALE = 0.25f;
};


#endif // !PARTICLE_H