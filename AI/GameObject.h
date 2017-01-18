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
	PowerUp_Shield,
	PowerUp_RapidFire,
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

	void					SetRegion(int region);
	int						RegionCheck(int position);

	void					TeleportRight(sf::Vector2f rightEdge);
	void					TeleportLeft(sf::Vector2f leftEdge);

	void					TeleportByAmount(sf::Vector2f amount);
	void					InsideRegion(bool inside);
	virtual void			CollisionEnter(GameObject*& objectCollided);

	sf::Vector2f			getPosition() const;
	sf::Vector2f			getSize() const;
	ObjectType				getType() const;
	int						getRegion() const;
	bool					isInsideRegion() const;
	bool					getAlive() const;

	void setSize(sf::Vector2f size);

protected:
	virtual void			initialize(sf::Vector2f position, sf::Texture &texture, ObjectType type);

protected:
	virtual void			draw(sf::RenderTarget& target, sf::RenderStates states) const;

protected:
	sf::Vector2f			_size;
	sf::Sprite				_sprite;
	ObjectType				_type;
	
	int						_region;
	bool					_insideRegion;
	bool					_isAlive;
};

