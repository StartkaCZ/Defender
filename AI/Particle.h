#ifndef PARTICLE_H
#define PARTICLE_H

#include <SFML/Graphics.hpp>

class Particle : public sf::Drawable, protected sf::NonCopyable
{
public:
						Particle(float timer, sf::Vector2f dir, float speed, sf::Vector2f position, sf::Texture& texture);

	void				Update(float dt);

	bool				isAlive() const;

protected:
	void				draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	float				_timer;
	float				_startTimer;
	bool				_alive;
	
	sf::Sprite			_sprite;
	sf::Vector2f		_velocity;

	const float			ALPHA = 255.f;
};


#endif // !PARTICLE_H