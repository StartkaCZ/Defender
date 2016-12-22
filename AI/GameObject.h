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
	Meteor,
	//power ups
	PowerUp,
	//Projectiles
	PlayerLazer,
};

class GameObject : public sf::Drawable, protected sf::NonCopyable, protected sf::Transformable
{
public:
							GameObject();
	virtual					~GameObject();

protected:
	virtual void			initialize(sf::Vector2f position, sf::Texture &texture, ObjectType type);

protected:
	virtual void			draw(sf::RenderTarget& target, sf::RenderStates states) const;

protected:
	sf::Sprite				_sprite;
	ObjectType				_type;
};

