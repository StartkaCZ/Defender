#include "GameObject.h"



GameObject::GameObject()
{
}


GameObject::~GameObject()
{
}

void GameObject::initialize(sf::Vector2f position, sf::Texture &texture, ObjectType type)
{
	_sprite = sf::Sprite();
	_sprite.setTexture(texture);
	_sprite.setOrigin(texture.getSize().x * 0.5f, texture.getSize().y * 0.5f);

	_size = sf::Vector2f(_sprite.getTextureRect().width, _sprite.getTextureRect().height)*0.5f;

	_type = type;

	setPosition(position);
}

void GameObject::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// Apply transform of current node
	states.transform *= getTransform();
	target.draw(_sprite, states);
}

sf::Vector2f GameObject::getPosition() const
{
	return Transformable::getPosition();
}


sf::Vector2f GameObject::getSize() const
{
	return _size;
}

void GameObject::setSize(sf::Vector2f size) 
{
	_size = size;
}


ObjectType GameObject::getType() const
{
	return _type;
}
