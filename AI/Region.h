#pragma once

#include "GameObject.h"

#include <SFML\Graphics.hpp>
#include <vector>

class Region : public sf::Drawable, protected sf::NonCopyable
{
public:
								Region();
								~Region();

	void						Initialize(sf::Vector2f position, sf::Texture& backgroundTexture, sf::Texture& foregroundTexture);
	int							Contained(sf::Vector2f position);

	void						AddGameObject(GameObject*& gameObject);
	void						RemoveGameObject(GameObject*& gameObject);
	void						Draw(sf::RenderWindow& renderWindow);

	bool						Teleport(float xPosition);
	
	std::vector<GameObject*>&	getGameObjects();
	sf::Vector2f				getPosition() const;
	sf::Vector2f				getSize() const;

protected:
	virtual void				draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	sf::Sprite					_backgroundTexture;
	sf::Sprite					_foregroundTexture;

	std::vector<GameObject*>	_gameObjectsWithin;
};

