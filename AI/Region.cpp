#include "Region.h"



Region::Region()
{
}


Region::~Region()
{
}

void Region::Initialize(sf::Vector2f position, sf::Texture& background, sf::Texture& foreground)
{
	_backgroundTexture.setTexture(background);
	_backgroundTexture.setPosition(position);

	_foregroundTexture.setTexture(foreground);
	_foregroundTexture.setPosition(position);
}

void Region::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_backgroundTexture, states);
	target.draw(_foregroundTexture, states);
}