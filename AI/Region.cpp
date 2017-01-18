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

void Region::DrawRegion(sf::RenderWindow& renderWindow)
{
	renderWindow.draw(*this);
}
void Region::DrawObjects(sf::RenderWindow& renderWindow)
{
	for (int i = 0; i < _gameObjectsWithin.size(); i++)
	{
		renderWindow.draw(*_gameObjectsWithin[i]);
	}
}

///<summary>
///Returns 1 if the position is ahead of the region.
///Returns 0 if the position is contained within the region.
///Returns -1 if the position is behind the region.
///</summary>
int Region::Contained(sf::Vector2f position)
{
	if (position.x < _backgroundTexture.getPosition().x)
	{
		return -1;
	}
	else if (position.x > _backgroundTexture.getPosition().x + _backgroundTexture.getTextureRect().width)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void Region::AddGameObject(GameObject*& gameObject)
{
	_gameObjectsWithin.push_back(gameObject);
}

void Region::RemoveGameObject(GameObject*& gameObject)
{
	for (int i = 0; i < _gameObjectsWithin.size(); i++)
	{
		if (_gameObjectsWithin[i] == gameObject)
		{
			_gameObjectsWithin.erase(_gameObjectsWithin.begin() + i);
		}
	}
}

bool Region::Teleport(float xPosition)
{
	if (getPosition().x == xPosition)
	{
		return true;
	}
	else
	{
		sf::Vector2f difference = sf::Vector2f(xPosition - getPosition().x, 0);

		for (int i = 0; i < _gameObjectsWithin.size(); i++)
		{
			_gameObjectsWithin[i]->TeleportByAmount(difference);
		}

		_backgroundTexture.setPosition(getPosition() + difference);
		_foregroundTexture.setPosition(_backgroundTexture.getPosition());

		return false;
	}
}

std::vector<GameObject*>& Region::getGameObjects()
{
	return _gameObjectsWithin;
}

sf::Vector2f Region::getPosition() const
{
	return _backgroundTexture.getPosition();
}
sf::Vector2f Region::getSize() const
{
	return sf::Vector2f(_backgroundTexture.getTextureRect().width, _backgroundTexture.getTextureRect().height);
}