#pragma once

#include <SFML/Graphics.hpp>

enum class ObjectType
{
	//Players, friendly units
	Player,
	Astronaut,
	//Enemies
	Abductor,
	Mutant,
	AlienNest,
	//obstacles
	Obstacle_Meteor,
	//power ups
	PowerUp_SuperJump,
	//Projectiles
	Projetile_PlayerLazer,
	Projetile_Interceptor,
	Projetile_Bullet
};

class GameObject : public sf::Drawable, protected sf::NonCopyable, protected sf::Transformable
{
public:
							GameObject();
	virtual					~GameObject();

	sf::Vector2f			getPosition() const;
	sf::Vector2f			getSize() const;
	ObjectType				getType() const;

	void setSize(sf::Vector2f size);

protected:
	virtual void			initialize(sf::Vector2f position, sf::Texture &texture, ObjectType type);

protected:
	virtual void			draw(sf::RenderTarget& target, sf::RenderStates states) const;

protected:
	sf::Vector2f			_size;
	sf::Sprite				_sprite;
	ObjectType				_type;
};

