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
};

class GameObject : public sf::Drawable, protected sf::NonCopyable, protected sf::Transformable
{
public:
							GameObject();
	virtual					~GameObject();

	virtual void			initialize(sf::Vector2f position, sf::Texture &texture);

protected:
	virtual void			draw(sf::RenderTarget& target, sf::RenderStates states) const;

protected:
	sf::Sprite				_sprite;
	ObjectType				_type;
};

