#include "GameObject.h"



GameObject::GameObject()
{
}


GameObject::~GameObject()
{
}

void GameObject::initialize(sf::Vector2f position, sf::Texture &texture)
{
	_sprite = sf::Sprite();
	_sprite.setTexture(texture);
	_sprite.setOrigin(texture.getSize().x * 0.5f, texture.getSize().y * 0.5f);

	setPosition(position);
}

void GameObject::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// Apply transform of current node
	states.transform *= getTransform();
	target.draw(_sprite, states);
}
