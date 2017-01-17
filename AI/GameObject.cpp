#include "GameObject.h"

#include "ConstHolder.h"

GameObject::GameObject()
	: _region(-1)
	, _insideRegion(false)
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

void GameObject::SetRegion(int region)
{
	_region = region;
}

///<summary>
///Returns 1 if the position is ahead of the region.
///Returns 0 if the position is contained within the region.
///Returns -1 if the position is behind the region.
///</summary>
int GameObject::RegionCheck(int position)
{
	_region += position;

	if (_region < 0)
	{
		return -1;
	}
	else if (_region > SCREEN_TIME_SIZE-1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void GameObject::CollisionEnter(GameObject*& objectCollided)
{

}

void GameObject::TeleportRight(sf::Vector2f rightEdge)
{
	_region = SCREEN_TIME_SIZE - 1;
	setPosition(rightEdge.x - getPosition().x, getPosition().y);
}
void GameObject::TeleportLeft(sf::Vector2f leftEdge)
{
	_region = 0;
	setPosition(getPosition().x - leftEdge.x, getPosition().y);
}

void GameObject::TeleportByAmount(sf::Vector2f amount)
{
	move(amount);
}

void GameObject::InsideRegion(bool inside)
{
	_insideRegion = inside;
}

sf::Vector2f GameObject::getPosition() const
{
	return Transformable::getPosition();
}
sf::Vector2f GameObject::getSize() const
{
	return _size;
}

ObjectType GameObject::getType() const
{
	return _type;
}

int GameObject::getRegion() const
{
	return _region;
}

bool GameObject::isInsideRegion() const
{
	return _insideRegion;
}